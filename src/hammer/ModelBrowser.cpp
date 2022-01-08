// ModelBrowser.cpp : implementation file
//

#include "stdafx.h"

#undef PropertySheet

#include "ModelBrowser.h"
#include "matsys_controls/mdlpanel.h"
#include "vgui_controls/TextEntry.h"
#include "vgui_controls/Splitter.h"
#include "vgui_controls/CheckButton.h"
#include "vgui_controls/Button.h"
#include "vgui_controls/PropertySheet.h"
#include "vgui_controls/PropertyPage.h"
#include "vgui_controls/TreeView.h"
#include "vgui_controls/ImageList.h"
#include "vgui_controls/ComboBox.h"

#include "KeyValues.h"
#include "vgui/KeyCode.h"
#include "vgui/IVGui.h"
#include "vgui/ISurface.h"
#include "texturesystem.h"
#include "utlntree.h"
#include "filesystem.h"

static LPCTSTR pszIniSection = "Model Browser";

DECLARE_HANDLE(AssetList_t);
#define ASSET_LIST_INVALID ((AssetList_t)(0xFFFF))
typedef unsigned short DirHandle_t;

bool AssetTreeViewSortFunc(KeyValues *node1, KeyValues *node2) {
    const char *pDir1 = node1->GetString("text", NULL);
    const char *pDir2 = node2->GetString("text", NULL);
    return Q_stricmp(pDir1, pDir2) < 0;
}

static int __cdecl AssetBrowserSortFunc(vgui::ListPanel *pPanel, const vgui::ListPanelItem &item1,
                                        const vgui::ListPanelItem &item2) {
    bool bRoot1 = item1.kv->GetInt("root") != 0;
    bool bRoot2 = item2.kv->GetInt("root") != 0;
    if (bRoot1 != bRoot2)
        return bRoot1 ? -1 : 1;
    const char *pString1 = item1.kv->GetString("asset");
    const char *pString2 = item2.kv->GetString("asset");
    return Q_stricmp(pString1, pString2);
}

static int __cdecl AssetBrowserModSortFunc(vgui::ListPanel *pPanel, const vgui::ListPanelItem &item1,
                                           const vgui::ListPanelItem &item2) {
    int nMod1 = item1.kv->GetInt("modIndex", -1);
    int nMod2 = item2.kv->GetInt("modIndex", -1);
    if (nMod1 != nMod2)
        return nMod1 - nMod2;
    return AssetBrowserSortFunc(pPanel, item1, item2);
}

class CAssetTreeView2 : public vgui::TreeView {
    DECLARE_CLASS_SIMPLE(CAssetTreeView2, vgui::TreeView);

public:
    CAssetTreeView2(vgui::Panel *parent, const char *name, const char *pRootFolderName, const char *pRootDir);

    virtual ~CAssetTreeView2() {}

    // Inherited from base classes
    virtual void GenerateChildrenOfNode(int itemIndex);

    virtual void ApplySchemeSettings(vgui::IScheme *pScheme);

    // Opens and selects the root folder
    void OpenRoot();

    // Purpose: Refreshes the active file list
    void RefreshFileList();

    // Adds a subdirectory
    DirHandle_t GetRootDirectory();

    DirHandle_t AddSubDirectory(DirHandle_t hParent, const char *pDirName);

    void ClearDirectories();

    // Selects a folder
    void SelectFolder(const char *pSubDir, const char *pPath);

private:
    // Allocates the root node
    void AllocateRootNode();

    // Purpose: Refreshes the active file list
    DirHandle_t RefreshTreeViewItem(int nItemIndex);

    // Sets an item to be colored as if its a menu
    void SetItemColorForDirectories(int nItemID);

    // Add a directory into the treeview
    void AddDirectoryToTreeView(int nParentItemIndex, const char *pFullParentPath, DirHandle_t hPath);

    // Selects an item in the tree
    bool SelectFolder_R(int nItemID, const char *pPath);

    CUtlString m_RootFolderName;
    CUtlString m_RootDirectory;
    vgui::ImageList m_Images;
    CUtlNTree<CUtlString, DirHandle_t> m_DirectoryStructure;
};


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAssetTreeView2::CAssetTreeView2(Panel *pParent, const char *pName, const char *pRootFolderName, const char *pRootDir)
        : BaseClass(pParent, pName), m_Images(false) {
    SetSortFunc(AssetTreeViewSortFunc);

    m_RootFolderName = pRootFolderName;
    m_RootDirectory = pRootDir;
    AllocateRootNode();

    // build our list of images
    m_Images.AddImage(vgui::scheme()->GetImage("resource/icon_folder", false));
    SetImageList(&m_Images, false);

    SETUP_PANEL(this);
}


//-----------------------------------------------------------------------------
// Purpose: Refreshes the active file list
//-----------------------------------------------------------------------------
void CAssetTreeView2::OpenRoot() {
    RemoveAll();

    // add the base node
    const char *pRootDir = m_DirectoryStructure[m_DirectoryStructure.Root()];
    KeyValues *pkv = new KeyValues("root");
    pkv->SetString("text", m_RootFolderName.Get());
    pkv->SetInt("root", 1);
    pkv->SetInt("expand", 1);
    pkv->SetInt("dirHandle", m_DirectoryStructure.Root());
    pkv->SetString("path", pRootDir);
    int iRoot = AddItem(pkv, GetRootItemIndex());
    pkv->deleteThis();
    ExpandItem(iRoot, true);
}


//-----------------------------------------------------------------------------
// Allocates the root node
//-----------------------------------------------------------------------------
void CAssetTreeView2::AllocateRootNode() {
    DirHandle_t hRoot = m_DirectoryStructure.Alloc();
    m_DirectoryStructure.SetRoot(hRoot);
    m_DirectoryStructure[hRoot] = m_RootDirectory;
}


//-----------------------------------------------------------------------------
// Adds a subdirectory (maintains sorted order)
//-----------------------------------------------------------------------------
DirHandle_t CAssetTreeView2::GetRootDirectory() {
    return m_DirectoryStructure.Root();
}

DirHandle_t CAssetTreeView2::AddSubDirectory(DirHandle_t hParent, const char *pDirName) {
    DirHandle_t hSubdir = m_DirectoryStructure.Alloc();
    m_DirectoryStructure[hSubdir] = pDirName;
    Q_strlower(m_DirectoryStructure[hSubdir].GetForModify());

    DirHandle_t hChild = m_DirectoryStructure.FirstChild(hParent);
    m_DirectoryStructure.LinkChildBefore(hParent, hChild, hSubdir);

    return hSubdir;
}

void CAssetTreeView2::ClearDirectories() {
    m_DirectoryStructure.RemoveAll();
    AllocateRootNode();
}


//-----------------------------------------------------------------------------
// Sets an item to be colored as if its a menu
//-----------------------------------------------------------------------------
void CAssetTreeView2::SetItemColorForDirectories(int nItemID) {
    // mark directories in orange
    SetItemFgColor(nItemID, Color(224, 192, 0, 255));
}


//-----------------------------------------------------------------------------
// Add a directory into the treeview
//-----------------------------------------------------------------------------
void CAssetTreeView2::AddDirectoryToTreeView(int nParentItemIndex, const char *pFullParentPath, DirHandle_t hPath) {
    const char *pDirName = m_DirectoryStructure[hPath].Get();
    KeyValues *kv = new KeyValues("node", "text", pDirName);

    char pFullPath[MAX_PATH];
    Q_snprintf(pFullPath, sizeof(pFullPath), "%s/%s", pFullParentPath, pDirName);
    Q_FixSlashes(pFullPath);
    Q_strlower(pFullPath);
    bool bHasSubdirectories = m_DirectoryStructure.FirstChild(hPath) != m_DirectoryStructure.InvalidIndex();
    kv->SetString("path", pFullPath);
    kv->SetInt("expand", bHasSubdirectories);
    kv->SetInt("image", 0);
    kv->SetInt("dirHandle", hPath);

    int nItemID = AddItem(kv, nParentItemIndex);
    kv->deleteThis();

    // mark directories in orange
    SetItemColorForDirectories(nItemID);
}


//-----------------------------------------------------------------------------
// override to incremental request and show p4 directories
//-----------------------------------------------------------------------------
void CAssetTreeView2::GenerateChildrenOfNode(int nItemIndex) {
    KeyValues *pkv = GetItemData(nItemIndex);

    const char *pFullParentPath = pkv->GetString("path", NULL);
    if (!pFullParentPath)
        return;

    DirHandle_t hPath = (DirHandle_t) pkv->GetInt("dirHandle", m_DirectoryStructure.InvalidIndex());
    if (hPath == m_DirectoryStructure.InvalidIndex())
        return;

    DirHandle_t hChild = m_DirectoryStructure.FirstChild(hPath);
    while (hChild != m_DirectoryStructure.InvalidIndex()) {
        AddDirectoryToTreeView(nItemIndex, pFullParentPath, hChild);
        hChild = m_DirectoryStructure.NextSibling(hChild);
    }
}


//-----------------------------------------------------------------------------
// Purpose: Refreshes the active file list
//-----------------------------------------------------------------------------
DirHandle_t CAssetTreeView2::RefreshTreeViewItem(int nItemIndex) {
    if (nItemIndex < 0)
        return m_DirectoryStructure.InvalidIndex();

    // Make sure the expand icons are set correctly
    KeyValues *pkv = GetItemData(nItemIndex);
    DirHandle_t hPath = (DirHandle_t) pkv->GetInt("dirHandle", m_DirectoryStructure.InvalidIndex());
    const char *pFullParentPath = pkv->GetString("path", NULL);
    bool bHasSubdirectories = m_DirectoryStructure.FirstChild(hPath) != m_DirectoryStructure.InvalidIndex();
    if (bHasSubdirectories != (pkv->GetInt("expand") != 0)) {
        pkv->SetInt("expand", bHasSubdirectories);
        ModifyItem(nItemIndex, pkv);
    }
    bool bIsExpanded = IsItemExpanded(nItemIndex);
    if (!bIsExpanded)
        return hPath;

    // Check all children + build a list of children we've already got
    int nChildCount = GetNumChildren(nItemIndex);
    DirHandle_t *pFoundHandles = (DirHandle_t *) _alloca(nChildCount * sizeof(DirHandle_t));
    memset(pFoundHandles, 0xFF, nChildCount * sizeof(DirHandle_t));
    for (int i = 0; i < nChildCount; ++i) {
        int nChildItemIndex = GetChild(nItemIndex, i);
        pFoundHandles[i] = RefreshTreeViewItem(nChildItemIndex);
    }

    // Check directory structure to see if other directories were added
    DirHandle_t hChild = m_DirectoryStructure.FirstChild(hPath);
    for (; hChild != m_DirectoryStructure.InvalidIndex(); hChild = m_DirectoryStructure.NextSibling(hChild)) {
        // Search for existence of this child already
        bool bFound = false;
        for (int j = 0; j < nChildCount; ++j) {
            if (pFoundHandles[j] == hChild) {
                pFoundHandles[j] = pFoundHandles[nChildCount - 1];
                --nChildCount;
                bFound = true;
                break;
            }
        }

        if (bFound)
            continue;

        // Child is new, add it
        AddDirectoryToTreeView(nItemIndex, pFullParentPath, hChild);
    }

    return hPath;
}

void CAssetTreeView2::RefreshFileList() {
    // Make sure the expand icons are set correctly
    RefreshTreeViewItem(GetRootItemIndex());
    InvalidateLayout();
}


//-----------------------------------------------------------------------------
// Selects a folder
//-----------------------------------------------------------------------------
bool CAssetTreeView2::SelectFolder_R(int nItemID, const char *pPath) {
    if (nItemID < 0)
        return false;

    KeyValues *kv = GetItemData(nItemID);
    const char *pTestPath = kv->GetString("path");
    if (!Q_stricmp(pTestPath, pPath)) {
        AddSelectedItem(nItemID, true, false, true);
        return true;
    }

    // Substring match..
    CUtlString str = pTestPath;
    str += '\\';
    if (Q_strnicmp(str, pPath, str.Length()))
        return false;

    ExpandItem(nItemID, true);

    int nChildCount = GetNumChildren(nItemID);
    for (int i = 0; i < nChildCount; ++i) {
        int nChildItemID = GetChild(nItemID, i);
        if (SelectFolder_R(nChildItemID, pPath))
            return true;
    }
    return false;
}

void CAssetTreeView2::SelectFolder(const char *pSubDir, const char *pPath) {
    char pTemp[MAX_PATH];
    Q_snprintf(pTemp, sizeof(pTemp), "%s\\%s", pSubDir, pPath);
    Q_StripTrailingSlash(pTemp);

    int nItem = GetRootItemIndex();
    SelectFolder_R(nItem, pTemp);
}


//-----------------------------------------------------------------------------
// setup a smaller font
//-----------------------------------------------------------------------------
void CAssetTreeView2::ApplySchemeSettings(vgui::IScheme *pScheme) {
    BaseClass::ApplySchemeSettings(pScheme);
    SetFont(pScheme->GetFont("DefaultSmall"));
    SetFgColor(Color(216, 222, 211, 255));
}

class CAssetCache2 {
public:
    struct CachedAssetInfo_t {
        CUtlString m_AssetName;
        int m_nModIndex;
    };

    struct ModInfo_t {
        CUtlString m_ModName;
        CUtlString m_Path;
    };

    CAssetCache2();

    // Mod iteration
    int ModCount() const;

    const ModInfo_t &ModInfo(int nIndex) const;

    // Building the mod list
    void BuildModList();

    AssetList_t FindAssetList(const char *pAssetType, const char *pSubDir, int nExtCount, const char **ppExt);

    bool BeginAssetScan(AssetList_t hList, bool bForceRescan = false);

    CAssetTreeView2 *GetFileTree(AssetList_t hList);

    int GetAssetCount(AssetList_t hList) const;

    const CachedAssetInfo_t &GetAsset(AssetList_t hList, int nIndex) const;

    void AddAsset(AssetList_t hList, const CachedAssetInfo_t &info);

    bool ContinueSearchForAssets(AssetList_t hList, float flDuration);

private:
    struct DirToCheck_t {
        CUtlString m_DirName;
        DirHandle_t m_hDirHandle;
    };

    struct CachedAssetList_t {
        CachedAssetList_t() {}

        CachedAssetList_t(const char *pSearchSubDir, int nExtCount, const char **ppSearchExt) :
                m_pSubDir(pSearchSubDir, Q_strlen(pSearchSubDir) + 1) {
            m_Ext.AddMultipleToTail(nExtCount, ppSearchExt);
        }

        CachedAssetList_t(const CachedAssetList_t &) {
            // Only used during insertion; do nothing
        }

        CUtlVector<CachedAssetInfo_t> m_AssetList;
        CAssetTreeView2 *m_pFileTree;

        CUtlString m_pSubDir;
        CUtlVector<const char *> m_Ext;

        CUtlLinkedList<DirToCheck_t> m_DirectoriesToCheck;
        FileFindHandle_t m_hFind;
        bool m_bAssetScanComplete;
    };

private:
    bool AddFilesInDirectory(CachedAssetList_t &list, const char *pStartingFile, const char *pFilePath,
                             DirHandle_t hDirHandle, float flStartTime, float flDuration);

    bool DoesExtensionMatch(CachedAssetList_t &list, const char *pFileName);

    void AddAssetToList(CachedAssetList_t &list, const char *pAssetName, int nModIndex);

private:
    // List of known mods
    CUtlVector<ModInfo_t> m_ModList;

    // List of cached assets
    CUtlRBTree<CachedAssetList_t> m_CachedAssets;

    // Have we built the mod list?
    bool m_bBuiltModList;

    static bool CachedAssetLessFunc(const CachedAssetList_t &src1, const CachedAssetList_t &src2);
};


//-----------------------------------------------------------------------------
// Static instance of the asset cache
//-----------------------------------------------------------------------------
static CAssetCache2 s_AssetCache;


//-----------------------------------------------------------------------------
// Map sort func
//-----------------------------------------------------------------------------
bool CAssetCache2::CachedAssetLessFunc(const CAssetCache2::CachedAssetList_t &src1,
                                       const CAssetCache2::CachedAssetList_t &src2) {
    int nRetVal = Q_stricmp(src1.m_pSubDir, src2.m_pSubDir) > 0;
    if (nRetVal != 0)
        return nRetVal > 0;

    int nCount = src1.m_Ext.Count();
    int nDiff = nCount - src2.m_Ext.Count();
    if (nDiff != 0)
        return nDiff > 0;

    for (int i = 0; i < nCount; ++i) {
        nRetVal = Q_stricmp(src1.m_Ext[i], src2.m_Ext[i]);
        if (nRetVal != 0)
            return nRetVal > 0;
    }

    return false;
}


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAssetCache2::CAssetCache2() : m_CachedAssets(0, 0, CachedAssetLessFunc) {
    m_bBuiltModList = false;
}


//-----------------------------------------------------------------------------
// Mod iteration
//-----------------------------------------------------------------------------
int CAssetCache2::ModCount() const {
    return m_ModList.Count();
}

const CAssetCache2::ModInfo_t &CAssetCache2::ModInfo(int nIndex) const {
    return m_ModList[nIndex];
}


//-----------------------------------------------------------------------------
// Building the mod list
//-----------------------------------------------------------------------------
void CAssetCache2::BuildModList() {
    if (m_bBuiltModList)
        return;

    m_bBuiltModList = true;

    m_ModList.RemoveAll();

    // Add all mods
    int nLen = g_pFullFileSystem->GetSearchPath("GAME", false, NULL, 0);
    char *pSearchPath = (char *) stackalloc(nLen * sizeof(char));
    g_pFullFileSystem->GetSearchPath("GAME", false, pSearchPath, nLen);
    char *pPath = pSearchPath;
    while (pPath) {
        char *pSemiColon = strchr(pPath, ';');
        if (pSemiColon) {
            *pSemiColon = 0;
        }

        Q_StripTrailingSlash(pPath);
        Q_FixSlashes(pPath);

        char pModName[MAX_PATH];
        Q_FileBase(pPath, pModName, sizeof(pModName));

        // Always start in an asset-specific directory
        //		char pAssetPath[MAX_PATH];
        //		Q_snprintf( pAssetPath, MAX_PATH, "%s\\%s", pPath, m_pAssetSubDir );
        //		Q_FixSlashes( pPath );

        int i = m_ModList.AddToTail();
        m_ModList[i].m_ModName.Set(pModName);
        m_ModList[i].m_Path.Set(pPath);

        pPath = pSemiColon ? pSemiColon + 1 : NULL;
    }
}


//-----------------------------------------------------------------------------
// Adds an asset to the list of assets of this type
//-----------------------------------------------------------------------------
void CAssetCache2::AddAssetToList(CachedAssetList_t &list, const char *pAssetName, int nModIndex) {
    int i = list.m_AssetList.AddToTail();
    CachedAssetInfo_t &info = list.m_AssetList[i];
    info.m_AssetName.Set(pAssetName);
    info.m_nModIndex = nModIndex;
}


//-----------------------------------------------------------------------------
// Extension matches?
//-----------------------------------------------------------------------------
bool CAssetCache2::DoesExtensionMatch(CachedAssetList_t &info, const char *pFileName) {
    char pChildExt[MAX_PATH];
    Q_ExtractFileExtension(pFileName, pChildExt, sizeof(pChildExt));

    // Check the extension matches
    int nCount = info.m_Ext.Count();
    for (int i = 0; i < nCount; ++i) {
        if (!Q_stricmp(info.m_Ext[i], pChildExt))
            return true;
    }

    return false;
}


//-----------------------------------------------------------------------------
// Recursively add all files matching the wildcard under this directory
//-----------------------------------------------------------------------------
bool CAssetCache2::AddFilesInDirectory(CachedAssetList_t &list, const char *pStartingFile, const char *pFilePath,
                                       DirHandle_t hCurrentDir, float flStartTime, float flDuration) {
    Assert(list.m_hFind != FILESYSTEM_INVALID_FIND_HANDLE);

    // generate children
    // add all the items
    int nModCount = m_ModList.Count();
    int nSubDirLen = list.m_pSubDir ? Q_strlen(list.m_pSubDir) : 0;
    const char *pszFileName = pStartingFile;
    while (pszFileName) {
        char pRelativeChildPath[MAX_PATH];
        Q_snprintf(pRelativeChildPath, MAX_PATH, "%s\\%s", pFilePath, pszFileName);

        if (g_pFullFileSystem->FindIsDirectory(list.m_hFind)) {
            if (Q_strnicmp(pszFileName, ".", 2) && Q_strnicmp(pszFileName, "..", 3)) {
                DirHandle_t hDirHandle = list.m_pFileTree->AddSubDirectory(hCurrentDir, pszFileName);
                int i = list.m_DirectoriesToCheck.AddToTail();
                list.m_DirectoriesToCheck[i].m_DirName = pRelativeChildPath;
                list.m_DirectoriesToCheck[i].m_hDirHandle = hDirHandle;
            }
        } else {
            // Check the extension matches
            if (DoesExtensionMatch(list, pszFileName)) {
                char pFullAssetPath[MAX_PATH];
                g_pFullFileSystem->RelativePathToFullPath(pRelativeChildPath, "GAME", pFullAssetPath,
                                                          sizeof(pFullAssetPath));

                int nModIndex = -1;
                for (int i = 0; i < nModCount; ++i) {
                    if (!Q_strnicmp(pFullAssetPath, m_ModList[i].m_Path, m_ModList[i].m_Path.Length())) {
                        nModIndex = i;
                        break;
                    }
                }

                if (nModIndex >= 0) {
                    // Strip 'subdir/' prefix
                    char *pAssetName = pRelativeChildPath;
                    if (list.m_pSubDir) {
                        if (!Q_strnicmp(list.m_pSubDir, pAssetName, nSubDirLen)) {
                            if (pAssetName[nSubDirLen] == '\\') {
                                pAssetName += nSubDirLen + 1;
                            }
                        }
                    }
                    strlwr(pAssetName);

                    AddAssetToList(list, pAssetName, nModIndex);
                }
            }
        }

        // Don't let the search go for too long at a time
        if (Plat_FloatTime() - flStartTime >= flDuration)
            return false;

        pszFileName = g_pFullFileSystem->FindNext(list.m_hFind);
    }

    return true;
}


//-----------------------------------------------------------------------------
// Recursively add all files matching the wildcard under this directory
//-----------------------------------------------------------------------------
bool CAssetCache2::ContinueSearchForAssets(AssetList_t hList, float flDuration) {
    CachedAssetList_t &list = m_CachedAssets[(int) hList];

    float flStartTime = Plat_FloatTime();
    while (list.m_DirectoriesToCheck.Count()) {
        const char *pFilePath = list.m_DirectoriesToCheck[list.m_DirectoriesToCheck.Head()].m_DirName;
        DirHandle_t hCurrentDir = list.m_DirectoriesToCheck[list.m_DirectoriesToCheck.Head()].m_hDirHandle;

        const char *pStartingFile;
        if (list.m_hFind == FILESYSTEM_INVALID_FIND_HANDLE) {
            char pSearchString[MAX_PATH];
            Q_snprintf(pSearchString, MAX_PATH, "%s\\*", pFilePath);

            // get the list of files
            pStartingFile = g_pFullFileSystem->FindFirstEx(pSearchString, "GAME", &list.m_hFind);
        } else {
            pStartingFile = g_pFullFileSystem->FindNext(list.m_hFind);
        }

        if (!AddFilesInDirectory(list, pStartingFile, pFilePath, hCurrentDir, flStartTime, flDuration))
            return false;

        g_pFullFileSystem->FindClose(list.m_hFind);
        list.m_hFind = FILESYSTEM_INVALID_FIND_HANDLE;
        list.m_DirectoriesToCheck.Remove(list.m_DirectoriesToCheck.Head());
    }
    list.m_bAssetScanComplete = true;
    return true;
}


//-----------------------------------------------------------------------------
// Asset cache iteration
//-----------------------------------------------------------------------------
bool CAssetCache2::BeginAssetScan(AssetList_t hList, bool bForceRescan) {
    CachedAssetList_t &list = m_CachedAssets[(int) hList];
    if (bForceRescan) {
        list.m_bAssetScanComplete = false;
        if (list.m_hFind != FILESYSTEM_INVALID_FIND_HANDLE) {
            g_pFullFileSystem->FindClose(list.m_hFind);
            list.m_hFind = FILESYSTEM_INVALID_FIND_HANDLE;
        }
        list.m_DirectoriesToCheck.RemoveAll();
    }

    if (list.m_bAssetScanComplete)
        return false;

    // This case occurs if we stopped the picker previously while in the middle of a scan
    if (list.m_hFind != FILESYSTEM_INVALID_FIND_HANDLE)
        return true;

    list.m_AssetList.RemoveAll();
    list.m_pFileTree->ClearDirectories();

    // Add all files, determine which mod they are in.
    int i = list.m_DirectoriesToCheck.AddToTail();
    list.m_DirectoriesToCheck[i].m_DirName = list.m_pSubDir;
    list.m_DirectoriesToCheck[i].m_hDirHandle = list.m_pFileTree->GetRootDirectory();
    return true;
}


//-----------------------------------------------------------------------------
// Asset cache iteration
//-----------------------------------------------------------------------------
AssetList_t
CAssetCache2::FindAssetList(const char *pAssetType, const char *pSubDir, int nExtCount, const char **ppExt) {
    CachedAssetList_t search(pSubDir, nExtCount, ppExt);
    int nIndex = m_CachedAssets.Find(search);
    if (nIndex == m_CachedAssets.InvalidIndex()) {
        nIndex = m_CachedAssets.Insert(search);
        CachedAssetList_t &list = m_CachedAssets[nIndex];
        list.m_pSubDir = pSubDir;
        list.m_Ext.AddMultipleToTail(nExtCount, ppExt);
        list.m_hFind = FILESYSTEM_INVALID_FIND_HANDLE;
        list.m_bAssetScanComplete = false;
        list.m_pFileTree = new CAssetTreeView2(NULL, "FolderFilter", pAssetType, pSubDir);
    }

    return (AssetList_t) nIndex;
}

CAssetTreeView2 *CAssetCache2::GetFileTree(AssetList_t hList) {
    if (hList == ASSET_LIST_INVALID)
        return NULL;
    return m_CachedAssets[(int) hList].m_pFileTree;
}

int CAssetCache2::GetAssetCount(AssetList_t hList) const {
    if (hList == ASSET_LIST_INVALID)
        return 0;
    return m_CachedAssets[(int) hList].m_AssetList.Count();
}

const CAssetCache2::CachedAssetInfo_t &CAssetCache2::GetAsset(AssetList_t hList, int nIndex) const {
    Assert(nIndex < GetAssetCount(hList));
    return m_CachedAssets[(int) hList].m_AssetList[nIndex];
}

class CBaseAssetPicker2 : public vgui::EditablePanel {
    DECLARE_CLASS_SIMPLE(CBaseAssetPicker2, vgui::EditablePanel);

public:
    CBaseAssetPicker2(vgui::Panel *pParent, const char *pAssetType,
                      const char *pExt, const char *pSubDir, const char *pTextType);

    virtual ~CBaseAssetPicker2();

    // overridden frame functions
    virtual void OnTick();

    virtual bool HasUserConfigSettings();

    virtual void ApplyUserConfigSettings(KeyValues *pUserConfig);

    virtual void GetUserConfigSettings(KeyValues *pUserConfig);

    virtual void OnCommand(const char *pCommand);

    // Purpose:
    virtual void OnKeyCodeTyped(vgui::KeyCode code);

    // Returns the selected asset name
    int GetSelectedAssetCount();

    const char *GetSelectedAsset(int nAssetIndex = -1);

    // Is multiselect enabled?
    bool IsMultiselectEnabled() const;

    // Sets the initial selected asset
    void SetInitialSelection(const char *pAssetName);

    // Set/get the filter
    void SetFilter(const char *pFilter);

    const char *GetFilter();

    // Purpose: refreshes the file tree
    void RefreshFileTree();

    virtual void Activate();

protected:
    // Creates standard controls. Allows the derived class to
    // add these controls to various splitter windows
    void CreateStandardControls(vgui::Panel *pParent, bool bAllowMultiselect = false);

    // Allows the picker to browse multiple asset types
    void AddExtension(const char *pExtension);

    // Derived classes have this called when the previewed asset changes
    virtual void OnSelectedAssetPicked(const char *pAssetName) {}

    // Derived classes have this called when the next selected asset is selected by default
    virtual void OnNextSelectionIsDefault() {}

    // Request focus of the filter box
    void RequestFilterFocus();

    // Rescan assets
    void RescanAssets();

    MESSAGE_FUNC_PARAMS(OnTextChanged, "TextChanged", kv);

    MESSAGE_FUNC_PARAMS(OnItemSelected, "ItemSelected", kv);

    MESSAGE_FUNC_PARAMS(OnCheckButtonChecked, "CheckButtonChecked", kv);

    MESSAGE_FUNC(OnFileSelected, "TreeViewItemSelected");

private:
    struct AssetInfo_t {
        int m_nAssetIndex;
        int m_nItemId;
    };

    void BuildAssetNameList();

    void RefreshAssetList();

    int GetSelectedAssetModIndex();

    // Is a particular asset visible?
    bool IsAssetVisible(int nAssetIndex);

    // Recursively add all files matching the wildcard under this directory
    void AddAssetToList(int nAssetIndex);

    // Update column headers
    void UpdateAssetColumnHeader();

    vgui::Splitter *m_pAssetSplitter;

    class CAssetTreeView2 *m_pFileTree;

    vgui::CheckButton *m_pSubDirCheck;
    vgui::TextEntry *m_pFilter;
    vgui::ListPanel *m_pAssetBrowser;
    vgui::TextEntry *m_pFullPath;
    vgui::ComboBox *m_pModSelector;
    vgui::Button *m_pRescanButton;

    AssetList_t m_hAssetList;
    CUtlString m_FolderFilter;
    CUtlString m_Filter;
    CUtlString m_SelectedAsset;
    CUtlVector<AssetInfo_t> m_AssetList;
    const char *m_pAssetType;
    const char *m_pAssetTextType;
    const char *m_pAssetExt;
    const char *m_pAssetSubDir;
    CUtlVector<const char *> m_ExtraAssetExt;
    bool m_bBuiltAssetList: 1;
    bool m_bFirstAssetScan: 1;
    bool m_bFinishedAssetListScan: 1;
    int m_nCurrentModFilter;
    int m_nMatchingAssets;
    bool m_bSubDirCheck;

    friend class CBaseAssetPickerFrame;
};


class CMDLPicker2 : public CBaseAssetPicker2 {
    DECLARE_CLASS_SIMPLE(CMDLPicker2, CBaseAssetPicker2);

public:

    enum PageType_t {
        PAGE_NONE = 0,
        PAGE_RENDER = 0x1,
        PAGE_SEQUENCES = 0x2,
        PAGE_ACTIVITIES = 0x4,
        PAGE_SKINS = 0x8,
        PAGE_INFO = 0x10,
        PAGE_ALL = 0xFFFFFFFF,
    };

    CMDLPicker2(vgui::Panel *pParent, int nFlags = PAGE_ALL);

    ~CMDLPicker2();

    // overridden frame functions
    virtual void PerformLayout();

    virtual void OnCommand(const char *pCommand);

    // Get current model
    void GetSelectedMDLName(char *pBuffer, int nMaxLen);

    // get current selected options page
    int GetSelectedPage();

    // Allows external apps to select a MDL
    void SelectMDL(const char *pRelativePath);

    // Set/Get Sequence
    void SelectSequence(const char *pSequenceName);

    const char *GetSelectedSequenceName();

    // Set/Get Activity
    void SelectActivity(const char *pActivityName);

    const char *GetSelectedActivityName();

    void SelectSkin(int nSkin);

    int GetSelectedSkin();

private:
    MESSAGE_FUNC_PARAMS(OnAssetSelected, "AssetSelected", params);

    virtual void OnSelectedAssetPicked(const char *pMDLName);

    void RefreshActivitiesAndSequencesList();

    void RefreshRenderSettings();

    int UpdateSkinsList();

    void UpdateInfoTab();

    int UpdatePropDataList(const char *pszPropData, bool &bIsStatic);

    // Plays the selected activity
    void PlaySelectedActivity();

    // Plays the selected sequence
    void PlaySelectedSequence();

    MESSAGE_FUNC_PARAMS(OnCheckButtonChecked, "CheckButtonChecked", kv);

    MESSAGE_FUNC_PARAMS(OnItemSelected, "ItemSelected", kv);

    MESSAGE_FUNC(OnPageChanged, "PageChanged");

    CMDLPanel *m_pMDLPreview;
    vgui::Splitter *m_pFileBrowserSplitter;
    vgui::Splitter *m_pPreviewSplitter;

    vgui::PropertySheet *m_pViewsSheet;
    vgui::PropertyPage *m_pRenderPage;
    vgui::PropertyPage *m_pSequencesPage;
    vgui::PropertyPage *m_pActivitiesPage;
    vgui::PropertyPage *m_pSkinsPage;
    vgui::PropertyPage *m_pInfoPage;

    vgui::ListPanel *m_pSequencesList;
    vgui::ListPanel *m_pActivitiesList;
    vgui::ListPanel *m_pSkinsList;
    vgui::ListPanel *m_pPropDataList;

    MDLHandle_t m_hSelectedMDL;

    int m_nFlags;

    friend class CMDLPicker2Frame;
};

CBaseAssetPicker2::CBaseAssetPicker2(vgui::Panel *pParent, const char *pAssetType,
                                     const char *pExt, const char *pSubDir, const char *pTextType) :
        BaseClass(pParent, "AssetPicker") {
    m_bBuiltAssetList = false;
    m_pAssetType = pAssetType;
    m_pAssetTextType = pTextType;
    m_pAssetExt = pExt;
    m_pAssetSubDir = pSubDir;
    m_bFinishedAssetListScan = false;
    m_bFirstAssetScan = false;
    m_nMatchingAssets = 0;
    m_bSubDirCheck = true;
    m_hAssetList = ASSET_LIST_INVALID;
}


//-----------------------------------------------------------------------------
// Purpose: Destructor
//-----------------------------------------------------------------------------
CBaseAssetPicker2::~CBaseAssetPicker2() {
    SaveUserConfig();

    // Detach!
    m_pFileTree->RemoveActionSignalTarget(this);
    m_pFileTree->SetParent((Panel *) NULL);
    m_pFileTree = NULL;
}


//-----------------------------------------------------------------------------
// Creates standard controls
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::CreateStandardControls(vgui::Panel *pParent, bool bAllowMultiselect) {
    using namespace vgui;
    int nExtCount = 1 + m_ExtraAssetExt.Count();
    const char **ppExt = (const char **) _alloca(nExtCount * sizeof(const char *));
    ppExt[0] = m_pAssetExt;
    if (nExtCount > 1) {
        memcpy(ppExt + 1, m_ExtraAssetExt.Base(), nExtCount - 1);
    }

    m_hAssetList = s_AssetCache.FindAssetList(m_pAssetType, m_pAssetSubDir, nExtCount, ppExt);

    m_pAssetSplitter = new vgui::Splitter(pParent, "AssetSplitter", SPLITTER_MODE_HORIZONTAL, 1);
    vgui::Panel * pSplitterTopSide = m_pAssetSplitter->GetChild(0);
    vgui::Panel * pSplitterBottomSide = m_pAssetSplitter->GetChild(1);

    // Combo box for mods
    m_pModSelector = new ComboBox(pSplitterTopSide, "ModFilter", 5, false);
    m_pModSelector->AddActionSignalTarget(this);

    // Rescan button
    m_pRescanButton = new Button(pSplitterTopSide, "RescanButton", "Rescan", this, "AssetRescan");

    // file browser tree controls
    m_pFileTree = s_AssetCache.GetFileTree(m_hAssetList);
    m_pFileTree->SetParent(pSplitterTopSide);
    m_pFileTree->AddActionSignalTarget(this);

    m_pSubDirCheck = new CheckButton(pSplitterTopSide, "SubDirCheck", "Check subfolders for files?");
    m_pSubDirCheck->SetSelected(true);
    m_pSubDirCheck->SetEnabled(false);
    m_pSubDirCheck->SetVisible(false);
    m_pSubDirCheck->AddActionSignalTarget(this);

    char pTemp[512];
    Q_snprintf(pTemp, sizeof(pTemp), "No .%s files", m_pAssetExt);
    m_pAssetBrowser = new vgui::ListPanel(pSplitterBottomSide, "AssetBrowser");
    m_pAssetBrowser->AddColumnHeader(0, "mod", "Mod", 52, 0);
    m_pAssetBrowser->AddColumnHeader(1, "asset", m_pAssetType, 128, ListPanel::COLUMN_RESIZEWITHWINDOW);
    m_pAssetBrowser->SetSelectIndividualCells(false);
    m_pAssetBrowser->SetMultiselectEnabled(bAllowMultiselect);
    m_pAssetBrowser->SetEmptyListText(pTemp);
    m_pAssetBrowser->SetDragEnabled(true);
    m_pAssetBrowser->AddActionSignalTarget(this);
    m_pAssetBrowser->SetSortFunc(0, AssetBrowserModSortFunc);
    m_pAssetBrowser->SetSortFunc(1, AssetBrowserSortFunc);
    m_pAssetBrowser->SetSortColumn(1);

    // filter selection
    m_pFilter = new TextEntry(pSplitterBottomSide, "FilterList");
    m_pFilter->AddActionSignalTarget(this);

    // full path
    m_pFullPath = new TextEntry(pSplitterBottomSide, "FullPath");
    m_pFullPath->SetEnabled(false);
    m_pFullPath->SetEditable(false);

    m_nCurrentModFilter = -1;
}


//-----------------------------------------------------------------------------
// Reads user config settings
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::ApplyUserConfigSettings(KeyValues *pUserConfig) {
    BaseClass::ApplyUserConfigSettings(pUserConfig);

    // Populates the mod list names
    RefreshAssetList();

    const char *pFilter = pUserConfig->GetString("filter", "");
    m_FolderFilter = pUserConfig->GetString("folderfilter", "");
    const char *pMod = pUserConfig->GetString("mod", "");
    SetFilter(pFilter);
    m_nCurrentModFilter = -1;
    if (pMod && pMod[0]) {
        int nCount = s_AssetCache.ModCount();
        for (int i = 0; i < nCount; ++i) {
            const CAssetCache2::ModInfo_t &modInfo = s_AssetCache.ModInfo(i);
            if (Q_stricmp(pMod, modInfo.m_ModName))
                continue;

            int nItemCount = m_pModSelector->GetItemCount();
            for (int j = 0; j < nItemCount; ++j) {
                int nItemID = m_pModSelector->GetItemIDFromRow(j);
                KeyValues *kv = m_pModSelector->GetItemUserData(nItemID);
                int nModIndex = kv->GetInt("mod");
                if (nModIndex == i) {
                    m_nCurrentModFilter = i;
                    m_pModSelector->ActivateItem(nItemID);
                    break;
                }
            }
            break;
        }
    }
}


//-----------------------------------------------------------------------------
// Purpose: returns user config settings for this control
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::GetUserConfigSettings(KeyValues *pUserConfig) {
    BaseClass::GetUserConfigSettings(pUserConfig);
    pUserConfig->SetString("filter", m_Filter);
    pUserConfig->SetString("folderfilter", m_FolderFilter);
    pUserConfig->SetString("mod", (m_nCurrentModFilter >= 0) ?
                                  s_AssetCache.ModInfo(m_nCurrentModFilter).m_ModName : "");
}


//-----------------------------------------------------------------------------
// Purpose: optimization, return true if this control has any user config settings
//-----------------------------------------------------------------------------
bool CBaseAssetPicker2::HasUserConfigSettings() {
    return true;
}


//-----------------------------------------------------------------------------
// Allows the picker to browse multiple asset types
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::AddExtension(const char *pExtension) {
    m_ExtraAssetExt.AddToTail(pExtension);
}


//-----------------------------------------------------------------------------
// Is multiselect enabled?
//-----------------------------------------------------------------------------
bool CBaseAssetPicker2::IsMultiselectEnabled() const {
    return m_pAssetBrowser->IsMultiselectEnabled();
}


//-----------------------------------------------------------------------------
// Sets the initial selected asset
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::SetInitialSelection(const char *pAssetName) {
    // This makes it so the background list filling code will automatically select this asset when it gets to it.
    m_SelectedAsset = pAssetName;

    if (pAssetName) {
        // Sometimes we've already refreshed our list with a bunch of cached resources and the item is already in the list,
        // so in that case just select it here.
        int cnt = m_pAssetBrowser->GetItemCount();
        for (int i = 0; i < cnt; i++) {
            KeyValues *kv = m_pAssetBrowser->GetItem(i);
            if (!kv)
                continue;

            const char *pTestAssetName = kv->GetString("asset");
            if (!pTestAssetName)
                continue;

            if (Q_stricmp(pTestAssetName, pAssetName) == 0) {
                m_pAssetBrowser->SetSelectedCell(i, 0);
                break;
            }
        }
    }
}


//-----------------------------------------------------------------------------
// Set/get the filter
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::SetFilter(const char *pFilter) {
    m_Filter = pFilter;
    m_pFilter->SetText(pFilter);
}

const char *CBaseAssetPicker2::GetFilter() {
    return m_Filter;
}


//-----------------------------------------------------------------------------
// Purpose: called to open
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::Activate() {
    RefreshAssetList();
    RequestFilterFocus();
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::OnKeyCodeTyped(vgui::KeyCode code) {
    if ((code == KEY_UP) || (code == KEY_DOWN) || (code == KEY_PAGEUP) || (code == KEY_PAGEDOWN)) {
        KeyValues *pMsg = new KeyValues("KeyCodeTyped", "code", code);
        vgui::ipanel()->SendMessage(m_pAssetBrowser->GetVPanel(), pMsg, GetVPanel());
        pMsg->deleteThis();
    } else {
        BaseClass::OnKeyCodeTyped(code);
    }
}


//-----------------------------------------------------------------------------
// Is a particular asset visible?
//-----------------------------------------------------------------------------
bool CBaseAssetPicker2::IsAssetVisible(int nAssetIndex) {
    const CAssetCache2::CachedAssetInfo_t &info = s_AssetCache.GetAsset(m_hAssetList, nAssetIndex);

    // Filter based on active mod
    int nModIndex = info.m_nModIndex;
    if ((m_nCurrentModFilter >= 0) && (m_nCurrentModFilter != nModIndex))
        return false;

    // Filter based on name
    const char *pAssetName = info.m_AssetName;
    if (!Q_strcmp(pAssetName, m_SelectedAsset))
        return true;

    if (m_Filter.Length() && !Q_stristr(pAssetName, m_Filter.Get()))
        return false;

    // Filter based on folder
    if (m_FolderFilter.Length() && Q_strnicmp(pAssetName, m_FolderFilter.Get(), m_FolderFilter.Length()))
        return false;

    // Filter based on subdirectory check
    if (!m_bSubDirCheck && strchr(pAssetName + m_FolderFilter.Length(), '\\'))
        return false;

    return true;
}


//-----------------------------------------------------------------------------
// Adds an asset from the cache to the list
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::AddAssetToList(int nAssetIndex) {
    const CAssetCache2::CachedAssetInfo_t &info = s_AssetCache.GetAsset(m_hAssetList, nAssetIndex);

    bool bInRootDir = !strchr(info.m_AssetName, '\\') && !strchr(info.m_AssetName, '/');

    KeyValues *kv = new KeyValues("node", "asset", info.m_AssetName);
    kv->SetString("mod", s_AssetCache.ModInfo(info.m_nModIndex).m_ModName);
    kv->SetInt("modIndex", info.m_nModIndex);
    kv->SetInt("root", bInRootDir);
    int nItemID = m_pAssetBrowser->AddItem(kv, 0, false, false);
    kv->deleteThis();

    if (m_pAssetBrowser->GetSelectedItemsCount() == 0 && !Q_strcmp(m_SelectedAsset, info.m_AssetName)) {
        m_pAssetBrowser->SetSelectedCell(nItemID, 0);
    }

    KeyValues *pDrag = new KeyValues("drag", "text", info.m_AssetName);
    if (m_pAssetTextType) {
        pDrag->SetString("texttype", m_pAssetTextType);
    }
    m_pAssetBrowser->SetItemDragData(nItemID, pDrag);

    int i = m_AssetList.AddToTail();
    m_AssetList[i].m_nAssetIndex = nAssetIndex;
    m_AssetList[i].m_nItemId = nItemID;

    bool bIsVisible = IsAssetVisible(i);
    m_pAssetBrowser->SetItemVisible(nItemID, bIsVisible);
    if (bIsVisible) {
        ++m_nMatchingAssets;
    }
}


#define ASSET_LIST_DIRECTORY_INITIAL_SEARCH_TIME 0.25f
#define ASSET_LIST_DIRECTORY_SEARCH_TIME 0.025f

//-----------------------------------------------------------------------------
// Continues to build the asset list
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::OnTick() {
    BaseClass::OnTick();

    int nPreAssetCount = s_AssetCache.GetAssetCount(m_hAssetList);

    // Stop getting called back once all assets have been found
    float flTime = m_bFirstAssetScan ? ASSET_LIST_DIRECTORY_INITIAL_SEARCH_TIME : ASSET_LIST_DIRECTORY_SEARCH_TIME;
    bool bFinished = s_AssetCache.ContinueSearchForAssets(m_hAssetList, flTime);

    if (m_bFirstAssetScan) {
        m_pFileTree->OpenRoot();
    }
    m_bFirstAssetScan = false;

    int nPostAssetCount = s_AssetCache.GetAssetCount(m_hAssetList);
    for (int i = nPreAssetCount; i < nPostAssetCount; ++i) {
        AddAssetToList(i);
    }

    if (bFinished) {
        vgui::ivgui()->RemoveTickSignal(GetVPanel());
        m_bFinishedAssetListScan = true;

        // Copy the current folder filter.. this is necessary
        // to finally select the folder loaded from the user config settings
        // in the free view (since it's finally populated at this point)
        // NOTE: if a user has changed the folder filter between startup
        // and this point, this should still work since m_FolderFilter should be updated
        m_pFileTree->SelectFolder(m_pAssetSubDir, m_FolderFilter);
        RefreshAssetList();
        return;
    }

    UpdateAssetColumnHeader();
}


//-----------------------------------------------------------------------------
// Builds the Bsp name list
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::BuildAssetNameList() {
    if (m_bBuiltAssetList)
        return;

    m_bBuiltAssetList = true;
    m_nMatchingAssets = 0;
    m_nCurrentModFilter = -1;

    // Build the list of known mods if we haven't
    s_AssetCache.BuildModList();

    m_pModSelector->RemoveAll();
    m_pModSelector->AddItem("All Mods", new KeyValues("Mod", "mod", -1));
    int nModCount = s_AssetCache.ModCount();
    for (int i = 0; i < nModCount; ++i) {
        const char *pModName = s_AssetCache.ModInfo(i).m_ModName;
        m_pModSelector->AddItem(pModName, new KeyValues("Mod", "mod", i));
    }
    m_pModSelector->ActivateItemByRow(0);

    // If we've already read in
    if (s_AssetCache.BeginAssetScan(m_hAssetList)) {
        m_bFirstAssetScan = true;
        m_bFinishedAssetListScan = false;
        vgui::ivgui()->AddTickSignal(GetVPanel(), 10);
    } else {
        m_bFirstAssetScan = false;
        m_bFinishedAssetListScan = true;
    }

    int nAssetCount = s_AssetCache.GetAssetCount(m_hAssetList);
    for (int i = 0; i < nAssetCount; ++i) {
        AddAssetToList(i);
    }
}


//-----------------------------------------------------------------------------
// Rescan assets
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::RescanAssets() {
    m_pAssetBrowser->RemoveAll();
    m_AssetList.RemoveAll();
    s_AssetCache.BeginAssetScan(m_hAssetList, true);
    m_bFirstAssetScan = true;
    m_nMatchingAssets = 0;

    if (m_bFinishedAssetListScan) {
        m_bFinishedAssetListScan = false;
        vgui::ivgui()->AddTickSignal(GetVPanel(), 10);
    }
}


//-----------------------------------------------------------------------------
// Command handler
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::OnCommand(const char *pCommand) {
    if (!Q_stricmp(pCommand, "AssetRescan")) {
        RescanAssets();
        return;
    }

    BaseClass::OnCommand(pCommand);
}


//-----------------------------------------------------------------------------
// Update column headers
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::UpdateAssetColumnHeader() {
    char pColumnTitle[512];
    Q_snprintf(pColumnTitle, sizeof(pColumnTitle), "%s (%d/%d)%s",
               m_pAssetType, m_nMatchingAssets, m_AssetList.Count(), m_bFinishedAssetListScan ? "" : " ...");
    m_pAssetBrowser->SetColumnHeaderText(1, pColumnTitle);
}


//-----------------------------------------------------------------------------
// Request focus of the filter box
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::RequestFilterFocus() {
    if (m_Filter.Length()) {
        m_pFilter->SelectAllOnFirstFocus(true);
    }
    m_pFilter->RequestFocus();
}


//-----------------------------------------------------------------------------
// Purpose: refreshes the asset list
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::RefreshAssetList() {
    BuildAssetNameList();

    // Check the filter matches
    int nCount = m_AssetList.Count();
    m_nMatchingAssets = 0;
    for (int i = 0; i < nCount; ++i) {
        // Filter based on active mod
        bool bIsVisible = IsAssetVisible(i);
        m_pAssetBrowser->SetItemVisible(m_AssetList[i].m_nItemId, bIsVisible);
        if (bIsVisible) {
            ++m_nMatchingAssets;
        }
    }

    UpdateAssetColumnHeader();
    m_pAssetBrowser->SortList();

    if ((m_pAssetBrowser->GetSelectedItemsCount() == 0) && (m_pAssetBrowser->GetItemCount() > 0)) {
        // Invoke a callback if the next selection will be a 'default' selection
        OnNextSelectionIsDefault();
        int nItemID = m_pAssetBrowser->GetItemIDFromRow(0);
        m_pAssetBrowser->SetSelectedCell(nItemID, 0);
    }

    m_pFileTree->RefreshFileList();
}


//-----------------------------------------------------------------------------
// Purpose: refreshes dialog on file folder changing
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::OnFileSelected() {
    // update list
    const char *pFolderFilter = "";
    int iItem = m_pFileTree->GetFirstSelectedItem();
    if (iItem >= 0) {
        KeyValues *pkv = m_pFileTree->GetItemData(iItem);
        pFolderFilter = pkv->GetString("path");

        // The first keys are always the subdir
        pFolderFilter += Q_strlen(m_pAssetSubDir);
        if (*pFolderFilter) {
            ++pFolderFilter;
        }
    }

    if (Q_stricmp(pFolderFilter, m_FolderFilter.Get())) {
        int nLen = Q_strlen(pFolderFilter);
        m_FolderFilter = pFolderFilter;
        if (nLen > 0) {
            m_FolderFilter += '\\';
        }
        RefreshAssetList();
    }
}


//-----------------------------------------------------------------------------
// Purpose: refreshes dialog on text changing
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::OnTextChanged(KeyValues *pKeyValues) {
    vgui::Panel * pSource = (vgui::Panel *) pKeyValues->GetPtr("panel");
    if (pSource == m_pFilter) {
        int nLength = m_pFilter->GetTextLength();
        char *pNewFilter = (char *) _alloca((nLength + 1) * sizeof(char));
        if (nLength > 0) {
            m_pFilter->GetText(pNewFilter, nLength + 1);
        } else {
            pNewFilter[0] = 0;
        }
        if (Q_stricmp(pNewFilter, m_Filter.Get())) {
            m_Filter.SetLength(nLength);
            m_Filter = pNewFilter;
            RefreshAssetList();
        }
        return;
    }

    if (pSource == m_pModSelector) {
        KeyValues *pKeyValues = m_pModSelector->GetActiveItemUserData();
        if (pKeyValues) {
            m_nCurrentModFilter = pKeyValues->GetInt("mod", -1);
            RefreshAssetList();
        }
        return;
    }
}


//-----------------------------------------------------------------------------
// Purpose: Updates preview when an item is selected
//-----------------------------------------------------------------------------
void CBaseAssetPicker2::OnItemSelected(KeyValues *kv) {
    Panel *pPanel = (Panel *) kv->GetPtr("panel", NULL);
    if (pPanel == m_pAssetBrowser) {
        int nCount = GetSelectedAssetCount();
        Assert(nCount > 0);
        const char *pSelectedAsset = GetSelectedAsset(nCount - 1);

        // Fill in the full path
        int nModIndex = GetSelectedAssetModIndex();
        char pBuf[MAX_PATH];
        Q_snprintf(pBuf, sizeof(pBuf), "%s\\%s\\%s",
                   s_AssetCache.ModInfo(nModIndex).m_Path.Get(), m_pAssetSubDir, pSelectedAsset);
        Q_FixSlashes(pBuf);
        m_pFullPath->SetText(pBuf);

        vgui::surface()->SetCursor(vgui::dc_waitarrow);
        OnSelectedAssetPicked(pSelectedAsset);
        return;
    }
}

void CBaseAssetPicker2::OnCheckButtonChecked(KeyValues *kv) {
    vgui::Panel * pSource = (vgui::Panel *) kv->GetPtr("panel");
    if (pSource == m_pSubDirCheck) {
        m_bSubDirCheck = m_pSubDirCheck->IsSelected();
        RefreshAssetList();
    }
}


//-----------------------------------------------------------------------------
// Returns the selceted asset count
//-----------------------------------------------------------------------------
int CBaseAssetPicker2::GetSelectedAssetCount() {
    return m_pAssetBrowser->GetSelectedItemsCount();
}


//-----------------------------------------------------------------------------
// Returns the selceted asset name
//-----------------------------------------------------------------------------
const char *CBaseAssetPicker2::GetSelectedAsset(int nAssetIndex) {
    int nSelectedAssetCount = m_pAssetBrowser->GetSelectedItemsCount();
    if (nAssetIndex < 0) {
        nAssetIndex = nSelectedAssetCount - 1;
    }
    if (nSelectedAssetCount <= nAssetIndex || nAssetIndex < 0)
        return NULL;

    int nIndex = m_pAssetBrowser->GetSelectedItem(nAssetIndex);
    KeyValues *pItemKeyValues = m_pAssetBrowser->GetItem(nIndex);
    return pItemKeyValues->GetString("asset");
}


//-----------------------------------------------------------------------------
// Returns the selceted asset mod index
//-----------------------------------------------------------------------------
int CBaseAssetPicker2::GetSelectedAssetModIndex() {
    if (m_pAssetBrowser->GetSelectedItemsCount() == 0)
        return NULL;

    int nIndex = m_pAssetBrowser->GetSelectedItem(0);
    KeyValues *pItemKeyValues = m_pAssetBrowser->GetItem(nIndex);
    return pItemKeyValues->GetInt("modIndex");
}


static int __cdecl MDLBrowserSortFunc(vgui::ListPanel *pPanel, const vgui::ListPanelItem &item1,
                                      const vgui::ListPanelItem &item2) {
    const char *string1 = item1.kv->GetString("mdl");
    const char *string2 = item2.kv->GetString("mdl");
    return stricmp(string1, string2);
}


//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CMDLPicker2::CMDLPicker2(vgui::Panel *pParent, int nFlags) :
        BaseClass(pParent, "MDL Files", "mdl", "models", "mdlName") {
    using namespace vgui;
    m_hSelectedMDL = MDLHANDLE_INVALID;

    m_nFlags = nFlags;    // remember what we show and what not

    m_pRenderPage = NULL;
    m_pSequencesPage = NULL;
    m_pActivitiesPage = NULL;
    m_pSkinsPage = NULL;
    m_pInfoPage = NULL;

    m_pSequencesList = NULL;
    m_pActivitiesList = NULL;

    // Horizontal splitter for mdls
    m_pFileBrowserSplitter = new Splitter(this, "FileBrowserSplitter", SPLITTER_MODE_VERTICAL, 1);

    float flFractions[] = {0.33f, 0.67f};

    m_pFileBrowserSplitter->RespaceSplitters(flFractions);

    vgui::Panel * pSplitterLeftSide = m_pFileBrowserSplitter->GetChild(0);
    vgui::Panel * pSplitterRightSide = m_pFileBrowserSplitter->GetChild(1);

    // Standard browser controls
    pSplitterLeftSide->RequestFocus();
    CreateStandardControls(pSplitterLeftSide, false);

    // property sheet - revisions, changes, etc.
    m_pPreviewSplitter = new Splitter(pSplitterRightSide, "PreviewSplitter", SPLITTER_MODE_HORIZONTAL, 1);

    vgui::Panel * pSplitterTopSide = m_pPreviewSplitter->GetChild(0);
    vgui::Panel * pSplitterBottomSide = m_pPreviewSplitter->GetChild(1);

    // MDL preview
    m_pMDLPreview = new CMDLPanel(pSplitterTopSide, "MDLPreview");
    SetSkipChildDuringPainting(m_pMDLPreview);

    m_pViewsSheet = new vgui::PropertySheet(pSplitterBottomSide, "ViewsSheet");
    m_pViewsSheet->AddActionSignalTarget(this);

    // now add wanted features
    if (nFlags & PAGE_RENDER) {
        m_pRenderPage = new vgui::PropertyPage(m_pViewsSheet, "RenderPage");

        m_pRenderPage->AddActionSignalTarget(this);

        m_pRenderPage->LoadControlSettingsAndUserConfig("resource/mdlpickerrender.res");

        RefreshRenderSettings();

        // ground
        Button *pSelectProbe = (Button *) m_pRenderPage->FindChildByName("ChooseLightProbe");
        pSelectProbe->AddActionSignalTarget(this);
    }

    if (nFlags & PAGE_SEQUENCES) {
        m_pSequencesPage = new vgui::PropertyPage(m_pViewsSheet, "SequencesPage");

        m_pSequencesList = new vgui::ListPanel(m_pSequencesPage, "SequencesList");
        m_pSequencesList->AddColumnHeader(0, "sequence", "sequence", 52, 0);
        m_pSequencesList->AddActionSignalTarget(this);
        m_pSequencesList->SetSelectIndividualCells(true);
        m_pSequencesList->SetEmptyListText("No .MDL file currently selected.");
        m_pSequencesList->SetDragEnabled(true);
        m_pSequencesList->SetAutoResize(Panel::PIN_TOPLEFT, Panel::AUTORESIZE_DOWNANDRIGHT, 6, 6, -6, -6);
    }

    if (nFlags & PAGE_ACTIVITIES) {
        m_pActivitiesPage = new vgui::PropertyPage(m_pViewsSheet, "ActivitiesPage");

        m_pActivitiesList = new vgui::ListPanel(m_pActivitiesPage, "ActivitiesList");
        m_pActivitiesList->AddColumnHeader(0, "activity", "activity", 52, 0);
        m_pActivitiesList->AddActionSignalTarget(this);
        m_pActivitiesList->SetSelectIndividualCells(true);
        m_pActivitiesList->SetEmptyListText("No .MDL file currently selected.");
        m_pActivitiesList->SetDragEnabled(true);
        m_pActivitiesList->SetAutoResize(Panel::PIN_TOPLEFT, Panel::AUTORESIZE_DOWNANDRIGHT, 6, 6, -6, -6);
    }

    if (nFlags & PAGE_SKINS) {
        m_pSkinsPage = new vgui::PropertyPage(m_pViewsSheet, "SkinsPage");

        m_pSkinsList = new vgui::ListPanel(m_pSkinsPage, "SkinsList");
        m_pSkinsList->AddColumnHeader(0, "skin", "skin", 52, 0);
        m_pSkinsList->AddActionSignalTarget(this);
        m_pSkinsList->SetSelectIndividualCells(true);
        m_pSkinsList->SetEmptyListText("No .MDL file currently selected.");
        m_pSkinsList->SetDragEnabled(true);
        m_pSkinsList->SetAutoResize(Panel::PIN_TOPLEFT, Panel::AUTORESIZE_DOWNANDRIGHT, 6, 6, -6, -6);
    }

    if (nFlags & PAGE_INFO) {
        m_pInfoPage = new vgui::PropertyPage(m_pViewsSheet, "InfoPage");

        m_pInfoPage->AddActionSignalTarget(this);

        m_pInfoPage->LoadControlSettingsAndUserConfig("resource/mdlpickerinfo.res");

        CheckButton *pTempCheck = (CheckButton *) m_pInfoPage->FindChildByName("PhysicsObject");
        pTempCheck->SetDisabledFgColor1(pTempCheck->GetFgColor());
        pTempCheck->SetDisabledFgColor2(pTempCheck->GetFgColor());
        pTempCheck = (CheckButton *) m_pInfoPage->FindChildByName("StaticObject");
        pTempCheck->SetDisabledFgColor1(pTempCheck->GetFgColor());
        pTempCheck->SetDisabledFgColor2(pTempCheck->GetFgColor());
        pTempCheck = (CheckButton *) m_pInfoPage->FindChildByName("DynamicObject");
        pTempCheck->SetDisabledFgColor1(pTempCheck->GetFgColor());
        pTempCheck->SetDisabledFgColor2(pTempCheck->GetFgColor());

        m_pPropDataList = new vgui::ListPanel(m_pInfoPage, "PropData");
        m_pPropDataList->AddColumnHeader(0, "key", "key", 250, ListPanel::COLUMN_FIXEDSIZE);
        m_pPropDataList->AddColumnHeader(1, "value", "value", 52, 0);
        m_pPropDataList->AddActionSignalTarget(this);
        m_pPropDataList->SetSelectIndividualCells(false);
        m_pPropDataList->SetEmptyListText("No prop_data available.");
        m_pPropDataList->SetDragEnabled(true);
        m_pPropDataList->SetAutoResize(Panel::PIN_TOPLEFT, Panel::AUTORESIZE_DOWNANDRIGHT, 6, 72, -6, -6);

        RefreshRenderSettings();
    }

    // Load layout settings; has to happen before pinning occurs in code
    LoadControlSettingsAndUserConfig("resource/mdlpicker.res");

    // Pages must be added after control settings are set up
    if (m_pRenderPage) {
        m_pViewsSheet->AddPage(m_pRenderPage, "Render");
    }
    if (m_pSequencesPage) {
        m_pViewsSheet->AddPage(m_pSequencesPage, "Sequences");
    }
    if (m_pActivitiesPage) {
        m_pViewsSheet->AddPage(m_pActivitiesPage, "Activities");
    }
    if (m_pSkinsPage) {
        m_pViewsSheet->AddPage(m_pSkinsPage, "Skins");
    }
    if (m_pInfoPage) {
        m_pViewsSheet->AddPage(m_pInfoPage, "Info");
    }
}

void CMDLPicker2::RefreshRenderSettings() {
    vgui::CheckButton *pToggle;

    if (!m_pRenderPage)
        return;

    // ground
    pToggle = (vgui::CheckButton *) m_pRenderPage->FindChildByName("NoGround");
    pToggle->AddActionSignalTarget(this);
    m_pMDLPreview->SetGroundGrid(!pToggle->IsSelected());

    // collision
    pToggle = (vgui::CheckButton *) m_pRenderPage->FindChildByName("Collision");
    pToggle->AddActionSignalTarget(this);
    m_pMDLPreview->SetCollsionModel(pToggle->IsSelected());

    // wireframe
    pToggle = (vgui::CheckButton *) m_pRenderPage->FindChildByName("Wireframe");
    pToggle->AddActionSignalTarget(this);
    m_pMDLPreview->SetWireFrame(pToggle->IsSelected());

    // lockview
    pToggle = (vgui::CheckButton *) m_pRenderPage->FindChildByName("LockView");
    pToggle->AddActionSignalTarget(this);
    m_pMDLPreview->SetLockView(pToggle->IsSelected());

    // look at camera
    pToggle = (vgui::CheckButton *) m_pRenderPage->FindChildByName("LookAtCamera");
    pToggle->AddActionSignalTarget(this);
    m_pMDLPreview->SetLookAtCamera(pToggle->IsSelected());
}


//-----------------------------------------------------------------------------
// Purpose: Destructor
//-----------------------------------------------------------------------------
CMDLPicker2::~CMDLPicker2() {
}


//-----------------------------------------------------------------------------
// Performs layout
//-----------------------------------------------------------------------------
void CMDLPicker2::PerformLayout() {
    // NOTE: This call should cause auto-resize to occur
    // which should fix up the width of the panels
    BaseClass::PerformLayout();

    int w, h;
    GetSize(w, h);

    // Layout the mdl splitter
    m_pFileBrowserSplitter->SetBounds(0, 0, w, h);
}


//-----------------------------------------------------------------------------
// Buttons on various pages
//-----------------------------------------------------------------------------
void CMDLPicker2::OnAssetSelected(KeyValues *pParams) {
    /*const char *pAsset = pParams->GetString( "asset" );

	char pProbeBuf[MAX_PATH];
	Q_snprintf( pProbeBuf, sizeof( pProbeBuf ), "materials/lightprobes/%s", pAsset );

	CDisableUndoScopeGuard sg;

	CDmElement *pLightProbe = NULL;
	g_pDataModel->RestoreFromFile( pProbeBuf, "GAME", NULL, &pLightProbe );
	if ( !pLightProbe )
	{
		char pBuf[1024];
		Q_snprintf( pBuf, sizeof( pBuf ), "Error loading lightprobe file '%s'!\n", pProbeBuf );
		vgui::MessageBox *pMessageBox = new vgui::MessageBox( "Error Loading File!\n", pBuf, GetParent() );
		pMessageBox->DoModal();
		return;
	}

	m_pMDLPreview->SetLightProbe( pLightProbe );
	g_pDataModel->RemoveFileId( pLightProbe->GetFileId() );*/

}


//-----------------------------------------------------------------------------
// Buttons on various pages
//-----------------------------------------------------------------------------
void CMDLPicker2::OnCommand(const char *pCommand) {
    if (!Q_stricmp(pCommand, "ChooseLightProbe")) {
        /*CAssetPickerFrame *pPicker = new CAssetPickerFrame( this, "Select Light Probe (.prb) File",
															"Light Probe", "prb", "materials/lightprobes", "lightprobe" );
		pPicker->DoModal();*/
        return;
    }

    BaseClass::OnCommand(pCommand);
}


//-----------------------------------------------------------------------------
// Purpose: rebuilds the list of activities
//-----------------------------------------------------------------------------
void CMDLPicker2::RefreshActivitiesAndSequencesList() {
    m_pActivitiesList->RemoveAll();
    m_pSequencesList->RemoveAll();
    m_pMDLPreview->SetSequence(0);

    if (m_hSelectedMDL == MDLHANDLE_INVALID) {
        m_pActivitiesList->SetEmptyListText("No .MDL file currently selected");
        m_pSequencesList->SetEmptyListText("No .MDL file currently selected");
        return;
    }

    m_pActivitiesList->SetEmptyListText(".MDL file contains no activities");
    m_pSequencesList->SetEmptyListText(".MDL file contains no sequences");

    studiohdr_t *hdr = g_pMDLCache->GetStudioHdr(m_hSelectedMDL);

    CUtlDict<int, unsigned short> activityNames(true, 0, hdr->GetNumSeq());

    for (int j = 0; j < hdr->GetNumSeq(); j++) {
        if ( /*g_viewerSettings.showHidden ||*/ !(hdr->pSeqdesc(j).flags & STUDIO_HIDDEN)) {
            const char *pActivityName = hdr->pSeqdesc(j).pszActivityName();
            if (pActivityName && pActivityName[0]) {
                // Multiple sequences can have the same activity name; only add unique activity names
                if (activityNames.Find(pActivityName) == activityNames.InvalidIndex()) {
                    KeyValues *pkv = new KeyValues("node", "activity", pActivityName);
                    int nItemID = m_pActivitiesList->AddItem(pkv, 0, false, false);

                    KeyValues *pDrag = new KeyValues("drag", "text", pActivityName);
                    pDrag->SetString("texttype", "activityName");
                    pDrag->SetString("mdl", g_pMDLCache->GetModelName(m_hSelectedMDL));
                    m_pActivitiesList->SetItemDragData(nItemID, pDrag);

                    activityNames.Insert(pActivityName, j);
                }
            }

            const char *pSequenceName = hdr->pSeqdesc(j).pszLabel();
            if (pSequenceName && pSequenceName[0]) {
                KeyValues *pkv = new KeyValues("node", "sequence", pSequenceName);
                int nItemID = m_pSequencesList->AddItem(pkv, 0, false, false);

                KeyValues *pDrag = new KeyValues("drag", "text", pSequenceName);
                pDrag->SetString("texttype", "sequenceName");
                pDrag->SetString("mdl", g_pMDLCache->GetModelName(m_hSelectedMDL));
                m_pSequencesList->SetItemDragData(nItemID, pDrag);
            }
        }
    }
}

//-----------------------------------------------------------------------------
// A MDL was selected
//-----------------------------------------------------------------------------
void CMDLPicker2::OnSelectedAssetPicked(const char *pMDLName) {
    char pRelativePath[MAX_PATH];
    if (pMDLName) {
        Q_snprintf(pRelativePath, sizeof(pRelativePath), "models\\%s", pMDLName);
        SelectMDL(pRelativePath);
    } else {
        SelectMDL(NULL);
    }
}


//-----------------------------------------------------------------------------
// Allows external apps to select a MDL
//-----------------------------------------------------------------------------
void CMDLPicker2::SelectMDL(const char *pRelativePath) {
    MDLHandle_t hSelectedMDL = pRelativePath ? g_pMDLCache->FindMDL(pRelativePath) : MDLHANDLE_INVALID;

    // We didn't change models after all...
    if (hSelectedMDL == m_hSelectedMDL) {
        // g_pMDLCache->FindMDL adds a reference by default we don't use, release it again
        if (hSelectedMDL != MDLHANDLE_INVALID) {
            g_pMDLCache->Release(hSelectedMDL);
        }
        return;
    }

    m_hSelectedMDL = hSelectedMDL;

    if (g_pMDLCache->IsErrorModel(m_hSelectedMDL)) {
        m_hSelectedMDL = MDLHANDLE_INVALID;
    }
    m_pMDLPreview->SetMDL(m_hSelectedMDL);

    m_pMDLPreview->LookAtMDL();


    if (m_nFlags & (PAGE_SKINS)) {
        UpdateSkinsList();
    }

    if (m_nFlags & (PAGE_INFO)) {
        UpdateInfoTab();
    }

    if (m_nFlags & (PAGE_ACTIVITIES | PAGE_SEQUENCES)) {
        RefreshActivitiesAndSequencesList();
    }

    // g_pMDLCache->FindMDL adds a reference by default we don't use, release it again
    if (hSelectedMDL != MDLHANDLE_INVALID) {
        g_pMDLCache->Release(hSelectedMDL);
    }

    PostActionSignal(new KeyValues("MDLPreviewChanged", "mdl", pRelativePath ? pRelativePath : ""));
}


//-----------------------------------------------------------------------------
// Purpose: updates revision view on a file being selected
//-----------------------------------------------------------------------------
void CMDLPicker2::OnCheckButtonChecked(KeyValues *kv) {
    //    RefreshMDLList();
    BaseClass::OnCheckButtonChecked(kv);
    RefreshRenderSettings();
}


void CMDLPicker2::GetSelectedMDLName(char *pBuffer, int nMaxLen) {
    Assert(nMaxLen > 0);
    if (GetSelectedAssetCount() > 0) {
        Q_snprintf(pBuffer, nMaxLen, "models\\%s", GetSelectedAsset());
    } else {
        pBuffer[0] = 0;
    }
}

//-----------------------------------------------------------------------------
// Gets the selected activity/sequence
//-----------------------------------------------------------------------------
int CMDLPicker2::GetSelectedPage() {
    if (m_pSequencesPage && (m_pViewsSheet->GetActivePage() == m_pSequencesPage))
        return PAGE_SEQUENCES;

    if (m_pActivitiesPage && (m_pViewsSheet->GetActivePage() == m_pActivitiesPage))
        return PAGE_ACTIVITIES;

    return PAGE_NONE;
}

const char *CMDLPicker2::GetSelectedSequenceName() {
    if (!m_pSequencesPage)
        return NULL;

    int nIndex = m_pSequencesList->GetSelectedItem(0);
    if (nIndex >= 0) {
        KeyValues *pkv = m_pSequencesList->GetItem(nIndex);
        return pkv->GetString("sequence", NULL);
    }

    return NULL;
}

const char *CMDLPicker2::GetSelectedActivityName() {
    if (!m_pActivitiesPage)
        return NULL;

    int nIndex = m_pActivitiesList->GetSelectedItem(0);
    if (nIndex >= 0) {
        KeyValues *pkv = m_pActivitiesList->GetItem(nIndex);
        return pkv->GetString("activity", NULL);
    }
    return NULL;
}

int CMDLPicker2::GetSelectedSkin() {
    if (!m_pSkinsPage)
        return NULL;

    int nIndex = m_pSkinsList->GetSelectedItem(0);
    if (nIndex >= 0) {
        return nIndex;
    }
    return NULL;
}

//-----------------------------------------------------------------------------
// Plays the selected activity
//-----------------------------------------------------------------------------
void CMDLPicker2::SelectActivity(const char *pActivityName) {
    studiohdr_t *pstudiohdr = g_pMDLCache->GetStudioHdr(m_hSelectedMDL);
    for (int i = 0; i < pstudiohdr->GetNumSeq(); i++) {
        mstudioseqdesc_t &seqdesc = pstudiohdr->pSeqdesc(i);
        if (stricmp(seqdesc.pszActivityName(), pActivityName) == 0) {
            // FIXME: Add weighted sequence selection logic?
            m_pMDLPreview->SetSequence(i);
            break;
        }
    }

    PostActionSignal(new KeyValues("SequenceSelectionChanged", "activity", pActivityName));
}


//-----------------------------------------------------------------------------
// Plays the selected sequence
//-----------------------------------------------------------------------------
void CMDLPicker2::SelectSequence(const char *pSequenceName) {
    studiohdr_t *pstudiohdr = g_pMDLCache->GetStudioHdr(m_hSelectedMDL);
    for (int i = 0; i < pstudiohdr->GetNumSeq(); i++) {
        mstudioseqdesc_t &seqdesc = pstudiohdr->pSeqdesc(i);
        if (!Q_stricmp(seqdesc.pszLabel(), pSequenceName)) {
            m_pMDLPreview->SetSequence(i);
            break;
        }
    }

    PostActionSignal(new KeyValues("SequenceSelectionChanged", "sequence", pSequenceName));
}

void CMDLPicker2::SelectSkin(int nSkin) {
    m_pMDLPreview->SetSkin(nSkin);
    PostActionSignal(new KeyValues("SkinSelectionChanged", "skin", nSkin));
}


//-----------------------------------------------------------------------------
// Purpose: Updates preview when an item is selected
//-----------------------------------------------------------------------------
void CMDLPicker2::OnItemSelected(KeyValues *kv) {
    Panel *pPanel = (Panel *) kv->GetPtr("panel", NULL);
    if (m_pSequencesList && (pPanel == m_pSequencesList)) {
        const char *pSequenceName = GetSelectedSequenceName();
        if (pSequenceName) {
            SelectSequence(pSequenceName);
        }
        return;
    }

    if (m_pActivitiesList && (pPanel == m_pActivitiesList)) {
        const char *pActivityName = GetSelectedActivityName();
        if (pActivityName) {
            SelectActivity(pActivityName);
        }
        return;
    }

    if (m_pSkinsList && (pPanel == m_pSkinsList)) {
        int nSelectedSkin = GetSelectedSkin();
        SelectSkin(nSelectedSkin);

        return;
    }

    BaseClass::OnItemSelected(kv);
}


//-----------------------------------------------------------------------------
// Purpose: Called when a page is shown
//-----------------------------------------------------------------------------
void CMDLPicker2::OnPageChanged() {
    if (m_pSequencesPage && (m_pViewsSheet->GetActivePage() == m_pSequencesPage)) {
        m_pSequencesList->RequestFocus();

        const char *pSequenceName = GetSelectedSequenceName();

        if (pSequenceName) {
            SelectSequence(pSequenceName);
        }
        return;
    }

    if (m_pActivitiesPage && (m_pViewsSheet->GetActivePage() == m_pActivitiesPage)) {
        m_pActivitiesList->RequestFocus();

        const char *pActivityName = GetSelectedActivityName();

        if (pActivityName) {
            SelectActivity(pActivityName);
        }
        return;
    }
}

int CMDLPicker2::UpdateSkinsList() {
    int nNumSkins = 0;

    if (m_pSkinsList) {
        m_pSkinsList->RemoveAll();

        studiohdr_t *hdr = g_pMDLCache->GetStudioHdr(m_hSelectedMDL);
        if (hdr) {
            nNumSkins = hdr->numskinfamilies;
            for (int i = 0; i < nNumSkins; i++) {
                char skinText[25] = "";
                sprintf(skinText, "skin%i", i);
                KeyValues *pkv = new KeyValues("node", "skin", skinText);
                m_pSkinsList->AddItem(pkv, 0, false, false);
            }
        }
    }

    return nNumSkins;
}

void CMDLPicker2::UpdateInfoTab() {
    using namespace vgui;
    studiohdr_t *hdr = g_pMDLCache->GetStudioHdr(m_hSelectedMDL);
    if (!hdr)
        return;

    int nMass = hdr->mass;
    Panel * pTempPanel = m_pInfoPage->FindChildByName("MassValue");
    char massBuff[10];
    itoa(nMass, massBuff, 10);
    ((vgui::Label *) pTempPanel)->SetText(massBuff);
    bool bIsStatic = hdr->flags & STUDIOHDR_FLAGS_STATIC_PROP;
    bool bIsPhysics = false;
    const char *buf = hdr->KeyValueText();
    Label *pTempLabel = (Label *) m_pInfoPage->FindChildByName("StaticText");
    pTempLabel->SetVisible(false);
    if (buf) {
        buf = Q_strstr(buf, "prop_data");
        if (buf) {
            int iPropDataCount = UpdatePropDataList(buf, bIsStatic);
            if (iPropDataCount) {
                bIsPhysics = true;
            }
        } else {
            m_pPropDataList->RemoveAll();
        }
    } else {
        m_pPropDataList->RemoveAll();
    }

    CheckButton *pTempCheck = (CheckButton *) m_pInfoPage->FindChildByName("StaticObject");
    pTempCheck->SetCheckButtonCheckable(true);
    pTempCheck->SetSelected(bIsStatic);
    pTempCheck->SetCheckButtonCheckable(false);
    pTempCheck = (CheckButton *) m_pInfoPage->FindChildByName("PhysicsObject");
    pTempCheck->SetCheckButtonCheckable(true);
    pTempCheck->SetSelected(bIsPhysics);
    pTempCheck->SetCheckButtonCheckable(false);
    pTempCheck = (CheckButton *) m_pInfoPage->FindChildByName("DynamicObject");
    pTempCheck->SetCheckButtonCheckable(true);
    pTempCheck->SetSelected(!bIsPhysics);
    pTempCheck->SetCheckButtonCheckable(false);


}

int CMDLPicker2::UpdatePropDataList(const char *pszPropData, bool &bIsStatic) {
    using namespace vgui;
    int iCount = 0;

    if (m_pPropDataList) {
        m_pPropDataList->RemoveAll();

        const char *endPropData = strchr(pszPropData, '}');
        char keyText[255] = "";
        char valueText[255] = "";
        const char *beginChunk = strchr(pszPropData, '\"');
        if (!beginChunk) {
            return 0;
        }
        beginChunk++;
        const char *endChunk = strchr(beginChunk, '\"');
        while (endChunk) {
            Q_memcpy(keyText, beginChunk, endChunk - beginChunk);
            beginChunk = endChunk + 1;
            beginChunk = strchr(beginChunk, '\"') + 1;
            endChunk = strchr(beginChunk, '\"');
            Q_memcpy(valueText, beginChunk, endChunk - beginChunk);
            if (!Q_strcmp(keyText, "allowstatic") && !Q_strcmp(valueText, "1")) {
                if (!bIsStatic) {
                    Label *pTempLabel = (Label *) m_pInfoPage->FindChildByName("StaticText");
                    pTempLabel->SetVisible(true);
                }
                bIsStatic &= true;
            }
            KeyValues *pkv = new KeyValues("node", "key", keyText, "value", valueText);
            m_pPropDataList->AddItem(pkv, 0, false, false);
            Q_memset(keyText, 0, 255);
            Q_memset(valueText, 0, 255);
            iCount++;
            beginChunk = endChunk + 1;
            beginChunk = strchr(beginChunk, '\"');
            if (!beginChunk || beginChunk > endPropData) {
                return iCount;
            }
            beginChunk++;
            endChunk = strchr(beginChunk, '\"');
        }
    }
    return iCount;
}



// CModelBrowser dialog

class CModelBrowserPanel : public vgui::EditablePanel {
public:
    CModelBrowserPanel(CModelBrowser *pBrowser, const char *panelName) :
            vgui::EditablePanel(NULL, panelName) {
        m_pBrowser = pBrowser;
    }

    virtual ~CModelBrowserPanel() {}

    virtual void OnSizeChanged(int newWide, int newTall) {
        // call Panel and not EditablePanel OnSizeChanged.
        Panel::OnSizeChanged(newWide, newTall);
    }

    virtual void OnCommand(const char *pCommand) {
        if (Q_strcmp(pCommand, "OK") == 0) {
            m_pBrowser->EndDialog(IDOK);
        } else if (Q_strcmp(pCommand, "Cancel") == 0) {
            m_pBrowser->EndDialog(IDCANCEL);
        }
    }

    virtual void OnKeyCodeTyped(vgui::KeyCode code) {
        vgui::EditablePanel::OnKeyCodeTyped(code);

        if (code == KEY_ENTER) {
            m_pBrowser->EndDialog(IDOK);
        } else if (code == KEY_ESCAPE) {
            m_pBrowser->EndDialog(IDCANCEL);
        }
    }

    virtual void OnMessage(const KeyValues *params, vgui::VPANEL ifromPanel) {
        vgui::EditablePanel::OnMessage(params, ifromPanel);

        if (Q_strcmp(params->GetName(), "MDLPreviewChanged") == 0) {
            m_pBrowser->UpdateStatusLine();
        }
    }

    CModelBrowser *m_pBrowser;
};

IMPLEMENT_DYNAMIC(CModelBrowser, CDialog)

CModelBrowser::CModelBrowser(CWnd *pParent /*=NULL*/)
        : CDialog(CModelBrowser::IDD, pParent) {
    m_pPicker = new CMDLPicker2(NULL);
    m_pStatusLine = new vgui::TextEntry(NULL, "StatusLine");
}

CModelBrowser::~CModelBrowser() {
}

void CModelBrowser::SetModelName(const char *pModelName) {
    char pszTempModelName[255];
    strcpy(pszTempModelName, pModelName);

    char *pszSelectedModel = strchr(pszTempModelName, '/');
    if (pszSelectedModel) {
        pszSelectedModel += 1;
        Q_FixSlashes(pszSelectedModel, '\\');
    }

    m_pPicker->SelectMDL(pModelName);
    m_pPicker->SetInitialSelection(pszSelectedModel);

    m_pStatusLine->SetText(pModelName);
}

void CModelBrowser::GetModelName(char *pModelName, int length) {
    m_pPicker->GetSelectedMDLName(pModelName, length);

    Q_FixSlashes(pModelName, '/');
}

void CModelBrowser::GetSkin(int &nSkin) {
    nSkin = m_pPicker->GetSelectedSkin();
}

void CModelBrowser::SetSkin(int nSkin) {
    m_pPicker->SelectSkin(nSkin);
}

void CModelBrowser::UpdateStatusLine() {
    char szModel[1024];

    m_pPicker->GetSelectedMDLName(szModel, sizeof(szModel));

    m_pStatusLine->SetText(szModel);

/*	MDLHandle_t hMDL = g_pMDLCache->FindMDL( szModel );

	studiohdr_t *hdr = g_pMDLCache->GetStudioHdr( hMDL );

	g_pMDLCache->Release( hMDL ); */
}

void CModelBrowser::SaveLoadSettings(bool bSave) {
    CString str;
    CRect rect;
    CWinApp *pApp = AfxGetApp();

    if (bSave) {
        GetWindowRect(rect);
        str.Format("%d %d %d %d", rect.left, rect.top, rect.right, rect.bottom);
        pApp->WriteProfileString(pszIniSection, "Position", str);
        pApp->WriteProfileString(pszIniSection, "Filter", m_pPicker->GetFilter());
    } else {
        str = pApp->GetProfileString(pszIniSection, "Position");

        if (!str.IsEmpty()) {
            sscanf(str, "%d %d %d %d", &rect.left, &rect.top, &rect.right, &rect.bottom);

            if (rect.left < 0) {
                ShowWindow(SW_SHOWMAXIMIZED);
            } else {
                MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, FALSE);
            }

            Resize();
        }

        str = pApp->GetProfileString(pszIniSection, "Filter");

        if (!str.IsEmpty()) {
            m_pPicker->SetFilter(str);
        }
    }
}


void CModelBrowser::DoDataExchange(CDataExchange *pDX) {
    CDialog::DoDataExchange(pDX);
}

void CModelBrowser::Resize() {
    // reposition controls
    CRect rect;
    GetClientRect(&rect);

    m_VGuiWindow.MoveWindow(rect);

    m_pPicker->SetBounds(0, 0, rect.Width(), rect.Height() - 32);
    m_pButtonCancel->SetPos(8, rect.Height() - 30);
    m_pButtonOK->SetPos(84, rect.Height() - 30);
    m_pStatusLine->SetBounds(160, rect.Height() - 30, max(100, rect.Width() - 166), 24);
}

void CModelBrowser::OnSize(UINT nType, int cx, int cy) {
    if (nType == SIZE_MINIMIZED || !IsWindow(m_VGuiWindow.m_hWnd)) {
        CDialog::OnSize(nType, cx, cy);
        return;
    }

    Resize();

    CDialog::OnSize(nType, cx, cy);
}


BEGIN_MESSAGE_MAP(CModelBrowser, CDialog)
                    ON_WM_SIZE()
                    ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CModelBrowser::PreTranslateMessage(MSG *pMsg) {
    // don't filter dialog message
    return CWnd::PreTranslateMessage(pMsg);
}

BOOL CModelBrowser::OnInitDialog() {
    CDialog::OnInitDialog();

    m_VGuiWindow.Create(NULL, _T("ModelViewer"), WS_VISIBLE | WS_CHILD, CRect(0, 0, 100, 100), this, 1001);

    vgui::EditablePanel *pMainPanel = new CModelBrowserPanel(this, "ModelBrowerPanel");

    m_VGuiWindow.SetParentWindow(&m_VGuiWindow);
    m_VGuiWindow.SetMainPanel(pMainPanel);
    pMainPanel->MakePopup(false, false);
    m_VGuiWindow.SetRepaintInterval(75);


    m_pPicker->SetParent(pMainPanel);
    m_pPicker->AddActionSignalTarget(pMainPanel);

    m_pButtonOK = new vgui::Button(pMainPanel, "OpenButton", "OK", pMainPanel, "OK");
    m_pButtonCancel = new vgui::Button(pMainPanel, "CancelButton", "Cancel", pMainPanel, "Cancel");

    m_pStatusLine->SetParent(pMainPanel);
    m_pStatusLine->SetEditable(false);

    SaveLoadSettings(false); // load

    m_pPicker->Activate();

    return TRUE;
}

void CModelBrowser::OnDestroy() {
    SaveLoadSettings(true); // save

    // model browser destoys our defualt cube map, reload it
    g_Textures.RebindDefaultCubeMap();

    CDialog::OnDestroy();
}

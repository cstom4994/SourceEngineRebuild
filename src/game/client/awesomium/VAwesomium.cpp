#include "cbase.h"
#include "inputsystem/iinputsystem.h"
#include "vstdlib/jobthread.h"
#include "materialsystem\imaterialsystem.h"

#include "awesomium/VAwesomium.h"
#include <vgui_controls/Controls.h>

#define DEPTH 4

using namespace vgui;
using namespace Awesomium;

int VAwesomium::m_iNumberOfViews = 0;

template <class ArrayType> 
size_t getArrayLen(ArrayType *d)
{
    size_t n;
    n = _msize((LPVOID)d) / sizeof(ArrayType);
    return n;
}

class CVAwesomiumTexture : public ITextureRegenerator
{
public:
	CVAwesomiumTexture()
	{
		Msg("inited");
		m_buffer = NULL;
		released = false;
		m_height = 0;
		m_width = 0;
		m_hidden = false;
	}

	virtual void RegenerateTextureBits( ITexture *pTexture, IVTFTexture *pVTFTexture, Rect_t *pRect )
	{
		if(true)
		{
			CPixelWriter pixelWriter;
			pixelWriter.SetPixelMemory( pVTFTexture->Format(), pVTFTexture->ImageData(0, 0, 0), pVTFTexture->RowSizeInBytes( 0 ) );

			if(m_buffer && m_height && m_width)
			{
				if(getArrayLen(m_buffer) / 4 != m_height * m_width)
					return;
				/* way 1
				for (int i = 0;i < m_height ;i++)
				{
					pixelWriter.Seek( m_width , i );
					for (int j=0;j< m_width * 4 ;j = j + 4)
					{
						int offset = i * m_width * 4 + j * 4;
						//if(m_buffer[offset] && m_buffer[offset + 1] && m_buffer[offset + 2] && m_buffer[offset + 3])
						pixelWriter.WritePixel(m_buffer[offset + 2],m_buffer[offset + 1],m_buffer[offset],m_buffer[offset + 3]);         
					}
				}
				*/
				int count = 0;
				int n = 0;
				for(int i = 0;i < m_height * m_width;i++)
				{
					if(count >= m_width)
					{
						count = 0;
						n++;
						pixelWriter.Seek( m_width , n );
					}
					int offset = i * 4;
					pixelWriter.WritePixel(m_buffer[offset + 2],m_buffer[offset + 1],m_buffer[offset],m_buffer[offset + 3]); //rgba
				}
			}
		}
	}

	virtual void Release()
	{
		released = true;
	}


	void SetBuffer(const unsigned char *buffer)
	{
		m_buffer = buffer;
	}

	void SetHeight(int height)
	{
		m_height = height;
	}

	void SetWidth(int width)
	{
		m_width = width;
	}

	void SetHidden(bool hidden)
	{
		m_hidden = hidden;
	}

	bool released;

private:
	bool m_hidden;
	int m_height;
	int m_width;
	const unsigned char *m_buffer;
};


VAwesomium::VAwesomium(Panel *parent, const char *panelName) : Panel(parent, panelName)
{
	m_iNumberOfViews++;
	
	m_iTexture = NULL;

	m_iRegen = NULL;

	m_iTextureId = surface()->CreateNewTextureID(true);

	m_WebCore = WebCore::instance();
	if( !m_WebCore )
	{
		WebConfig config;
		config.remote_debugging_port = 1337;
		config.additional_options.Push(WSLit("--allow-file-access-from-files"));
		m_WebCore =  WebCore::Initialize(config);
	}

	

	m_WebView = m_WebCore->CreateWebView(GetTall(), GetWide());
	m_WebView->set_js_method_handler(this);
	m_WebView->set_load_listener(this);
	if(!m_WebView->IsTransparent())
		m_WebView->SetTransparent(true);
	
	SetPaintEnabled(true);
	SetPaintBackgroundEnabled(false);
	SetBgColor(Color(0,0,0,0));

	ResizeView();
	//SetNextClientThink( CLIENT_THINK_ALWAYS );
}

VAwesomium::~VAwesomium()
{
	m_iNumberOfViews--;
	
	m_WebView->Destroy();
	
	if( m_WebCore && m_iNumberOfViews == 0 )
	{
		m_WebCore->Shutdown();	
	}

	m_WebView = NULL;
	m_WebCore = NULL;
	m_BitmapSurface = NULL;
}

Awesomium::WebView* VAwesomium::GetWebView()
{
	return m_WebView;
}

void VAwesomium::ExecuteJavaScript(const char *script, const char *frame_xpath)
{
	m_WebView->ExecuteJavascript(WSLit(script), WSLit(frame_xpath));
}



void VAwesomium::Think()
{
	//VCRHook_CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)VAwesomium::UpdateWebCore, NULL,NULL,NULL);
	m_WebCore->Update();
	//Sleep(10);
	//ThreadExecute(UpdateCoreThread,0);
	if(m_iRegen)
		((CVAwesomiumTexture *)m_iRegen)->SetHidden(!this->IsVisible());
}

void VAwesomium::Paint()
{
	BaseClass::Paint();

	m_BitmapSurface = (BitmapSurface*)m_WebView->surface();

	if (m_BitmapSurface && m_iNearestPowerWidth + m_iNearestPowerHeight > 0)
	{
		AllocateViewBuffer();
		DrawBrowserView();
	}

}

int VAwesomium::NearestPowerOfTwo(int v)
{
	// http://stackoverflow.com/questions/466204/rounding-off-to-nearest-power-of-2
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

void VAwesomium::AllocateViewBuffer()
{
	//IVTFTexture *tex = CreateVTFTexture();
	//tex->Init(m_BitmapSurface->width(),m_BitmapSurface->height(),4,IMAGE_FORMAT_BGRA8888,TEXTUREFLAGS_NOMIP | TEXTUREFLAGS_PROCEDURAL,1);
	//tex->
	
	if(!m_iTexture)
	{
		m_iTexture = g_pMaterialSystem->CreateProceduralTexture("_pt_vawe",TEXTURE_GROUP_VGUI,m_iNearestPowerWidth,m_iNearestPowerHeight,IMAGE_FORMAT_BGRA8888,TEXTUREFLAGS_NOMIP);
	}
	
	Assert(!m_iTexture->IsProcedural());

	if(!m_iRegen)
	{
		m_iRegen = new CVAwesomiumTexture();
		((CVAwesomiumTexture *)m_iRegen)->SetHeight(m_iNearestPowerHeight);
		((CVAwesomiumTexture *)m_iRegen)->SetWidth(m_iNearestPowerWidth);
		m_iTexture->SetTextureRegenerator(m_iRegen);
	}

	if(((CVAwesomiumTexture *)m_iRegen)->released)
	{
		delete m_iRegen;
		m_iRegen = NULL;
		m_iRegen = new CVAwesomiumTexture();
		((CVAwesomiumTexture *)m_iRegen)->SetHeight(m_iNearestPowerHeight);
		((CVAwesomiumTexture *)m_iRegen)->SetWidth(m_iNearestPowerWidth);
		m_iTexture->SetTextureRegenerator(m_iRegen);
	}

	if(m_BitmapSurface)
	{
		if(m_BitmapSurface->is_dirty())
		{
			((CVAwesomiumTexture *)m_iRegen)->SetHeight(m_iNearestPowerHeight);
			((CVAwesomiumTexture *)m_iRegen)->SetWidth(m_iNearestPowerWidth);
			unsigned char* buffer = new unsigned char[m_iNearestPowerWidth * m_iNearestPowerHeight * DEPTH];
			m_BitmapSurface->CopyTo(buffer, m_iNearestPowerWidth * DEPTH, DEPTH, false, false);
			if(buffer)
				((CVAwesomiumTexture *)m_iRegen)->SetBuffer(buffer);
			m_iTexture->Download();
			delete buffer;
			buffer = NULL;
		}	
	}


	//unsigned char* buffer = new unsigned char[m_iNearestPowerWidth * m_iNearestPowerHeight * DEPTH];
	//m_BitmapSurface->CopyTo(buffer, m_BitmapSurface->width() * DEPTH, DEPTH, true, false);
	//vgui::surface()->DrawSetTextureRGBA(m_iTextureId, m_BitmapSurface->buffer(), m_BitmapSurface->width(), m_BitmapSurface->height(), true,true);
	vgui::surface()->DrawSetTextureFile(m_iTextureId,"ui/awesomium_surface",true,true);
	//delete buffer;
	//buffer = NULL;
}

void VAwesomium::DrawBrowserView()
{
	vgui::surface()->DrawSetTexture(m_iTextureId);
	vgui::surface()->DrawSetColor(255, 255, 255, 255);

	float scalerW = float(m_BitmapSurface->width()) / float(m_iNearestPowerWidth);
	float scalerT = float(m_BitmapSurface->height()) / float(m_iNearestPowerHeight);

	//vgui::surface()->DrawTexturedRect( 0,0,ScreenWidth(),ScreenHeight());
	vgui::surface()->DrawTexturedSubRect(0, 0, m_BitmapSurface->width(), m_BitmapSurface->height(), 0.0f, 0.0f, scalerW, scalerT);
	
}

void VAwesomium::OnCursorMoved(int x, int y)
{
	m_WebView->InjectMouseMove(x, y);
}

void VAwesomium::OnRequestFocus(vgui::VPANEL subFocus, vgui::VPANEL defaultPanel)
{
	BaseClass::OnRequestFocus(subFocus, defaultPanel);
	m_WebView->Focus();
}

void VAwesomium::OnMousePressed(MouseCode code)
{
	MouseButtonHelper(code, false);
}

void VAwesomium::OnMouseReleased(MouseCode code)
{
	MouseButtonHelper(code, true);
}

void VAwesomium::MouseButtonHelper(MouseCode code, bool isUp)
{
	MouseButton mouseButton;

	switch (code)
	{
	case MOUSE_RIGHT:
		mouseButton = kMouseButton_Right;
		break;
	case MOUSE_MIDDLE:
		mouseButton = kMouseButton_Middle;
		break;
	default: // MOUSE_LEFT:
		mouseButton = kMouseButton_Left;
		break;
	}

	isUp ? m_WebView->InjectMouseUp(mouseButton) : m_WebView->InjectMouseDown(mouseButton);
}

void VAwesomium::OnMouseWheeled(int delta)
{
	//m_WebView->InjectMouseWheel(delta * MOUSE_COUNT, 0);
}

void VAwesomium::OnKeyTyped(wchar_t unichar)
{
	WebKeyboardEvent event;

	event.text[0] = unichar;
	event.type = WebKeyboardEvent::kTypeChar;
	m_WebView->InjectKeyboardEvent(event);
}

void VAwesomium::KeyboardButtonHelper(KeyCode code, bool isUp)
{
	WebKeyboardEvent event;
	
	event.virtual_key_code = inputsystem->ButtonCodeToVirtualKey(code);
	event.type = isUp ? WebKeyboardEvent::kTypeKeyUp : WebKeyboardEvent::kTypeKeyDown;

	m_WebView->InjectKeyboardEvent(event);
}

void VAwesomium::OnKeyCodePressed(KeyCode code)
{
	KeyboardButtonHelper(code, false);
}

void VAwesomium::OnKeyCodeReleased(KeyCode code)
{
	KeyboardButtonHelper(code, true);
}

void VAwesomium::ResizeView()
{
	m_iNearestPowerWidth = NearestPowerOfTwo(GetWide());
	m_iNearestPowerHeight = NearestPowerOfTwo(GetTall());
	m_WebView->Resize(GetWide(), GetTall());
}

void VAwesomium::OpenURL(const char *address)
{
	m_WebView->LoadURL(WebURL(WSLit("about:blank")));
	m_WebView->LoadURL(WebURL(WSLit(address)));
	ResizeView();
}

void VAwesomium::OpenFile(std::string file)
{
	file = file.insert(0,"//ui//");
	file = file.insert(0,engine->GetGameDirectory());

	char* address = const_cast<char*>(file.c_str());
	
	m_WebView->LoadURL(WebURL(WSLit("about:blank")));
	m_WebView->LoadURL(WebURL(WSLit(address)));

	ResizeView();
}

void VAwesomium::PerformLayout()
{
	BaseClass::PerformLayout();
	ResizeView();
}

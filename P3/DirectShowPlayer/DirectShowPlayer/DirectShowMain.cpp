#include "pch.h"
#include "DirectShowMain.h"

DirectShowMain::DirectShowMain()
    : pGraph(nullptr), pMediaControl(nullptr), pEvent(nullptr), pVidWin(nullptr), pSeek(nullptr)
{
    CoInitialize(NULL); // zur Initialisierung des COM-Interfaces
}

DirectShowMain::~DirectShowMain()
{
    CleanUp();
}

HRESULT DirectShowMain::Initialize()
{
    // Erstelle Filter Graph Manager
    HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder, (void**)&pGraph);
    if (FAILED(hr))
        return hr;

    hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);
    if (FAILED(hr))
        return hr;

    hr = pGraph->QueryInterface(IID_IMediaEventEx, (void**)&pEvent);
    if (FAILED(hr))
        return hr;

    hr = pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeek);
    if (FAILED(hr))
        return hr;

    hr = pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWin);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

HRESULT DirectShowMain::ConfigureVideoWindow(HWND hwnd, UINT WM_GRAPHNOTIFY)
{
    //  Einstellen des Benachrichtigungsfensters
    HRESULT hr = pEvent->SetNotifyWindow((OAHWND)hwnd, WM_GRAPHNOTIFY, 0);
    if (FAILED(hr))
        return hr;

    // Eigentümer und Stil des Videofensters festlegen
    hr = pVidWin->put_Owner((OAHWND)hwnd);
    if (FAILED(hr))
        return hr;

    hr = pVidWin->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
    if (FAILED(hr))
        return hr;

    // Nachrichtenbehandlung (Maus, Keyboard)
    hr = pVidWin->put_MessageDrain((OAHWND)hwnd);
    if (FAILED(hr))
        return hr;
}

HRESULT DirectShowMain::LoadFile(const CString& filePath)
{
    return pGraph->RenderFile(filePath, NULL);
}

HRESULT DirectShowMain::Play()
{
    if (pMediaControl)
        return pMediaControl->Run();
    return E_FAIL;
}

HRESULT DirectShowMain::Pause()
{
    if (pMediaControl)
        return pMediaControl->Pause();
    return E_FAIL;
}

HRESULT DirectShowMain::Stop()
{
    if (pMediaControl) 
        pMediaControl->Stop();
    return E_FAIL;
}

HRESULT DirectShowMain::SeekToPosition(REFERENCE_TIME pos)
{
    if (pSeek)
        return pSeek->SetPositions(&pos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
    return E_FAIL;
}

HRESULT DirectShowMain::GetCurrentPosition(REFERENCE_TIME* pCurrent)
{
    if (pSeek)
        return pSeek->GetCurrentPosition(pCurrent);
    return E_FAIL;
}

HRESULT DirectShowMain::GetDuration(REFERENCE_TIME* pDuration)
{
    if (pSeek)
        return pSeek->GetDuration(pDuration);
    return E_FAIL;
}

HRESULT DirectShowMain::HandleGraphEvent()
{
    long evCode;
    LONG_PTR param1, param2;
    while (pEvent && SUCCEEDED(pEvent->GetEvent(&evCode, &param1, &param2, 0)))
    {
        pEvent->FreeEventParams(evCode, param1, param2);
        if (evCode == EC_COMPLETE || evCode == EC_USERABORT)
        {
            Stop();
            CleanUp();
            return S_OK;
        }
    }
    return S_OK;
}

HRESULT DirectShowMain::SetFullScreenMode(bool bFullScreen)
{
    if (pVidWin)
        return pVidWin->put_FullScreenMode(bFullScreen ? OATRUE : OAFALSE);
    return E_FAIL;
}

HRESULT DirectShowMain::SetVideoWindowPosition(long Left, long Top, long Width, long Height)
{
    if (pVidWin)
        return pVidWin->SetWindowPosition(Left, Top, Width, Height);
    return E_FAIL;
}

void DirectShowMain::CleanUp()
{
    // Release all COM interfaces and reset pointers
    if (pVidWin)
    {
        pVidWin->put_Visible(OAFALSE);
        pVidWin->put_Owner(NULL);
        pVidWin->Release();
        pVidWin = nullptr;
    }
    if (pSeek)
    {
        pSeek->Release();
        pSeek = nullptr;
    }
    if (pMediaControl)
    {
        pMediaControl->Release();
        pMediaControl = nullptr;
    }
    if (pEvent)
    {
        pEvent->Release();
        pEvent = nullptr;
    }
    if (pGraph)
    {
        pGraph->Release();
        pGraph = nullptr;
    }
}
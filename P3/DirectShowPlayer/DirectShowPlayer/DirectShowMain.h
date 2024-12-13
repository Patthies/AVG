#pragma once
class DirectShowMain
{
public:
    DirectShowMain();
    ~DirectShowMain();

    HRESULT Initialize();
    HRESULT ConfigureVideoWindow(HWND hwnd, UINT WM_GRAPHNOTIFY);
    HRESULT LoadFile(const CString& filePath);
    HRESULT Play();
    HRESULT Pause();
    HRESULT Stop();
    HRESULT SeekToPosition(REFERENCE_TIME pos);
    HRESULT GetCurrentPosition(REFERENCE_TIME* pCurrent);
    HRESULT GetDuration(REFERENCE_TIME* pDuration);
    HRESULT HandleGraphEvent();
    HRESULT SetFullScreenMode(bool bFullScreen);
    HRESULT SetVideoWindowPosition(long Left, long Top, long Width, long Height);
    void CleanUp();

private:
    IGraphBuilder* pGraph;       // Pointer to the COM interface
    IMediaControl* pMediaControl;
    IMediaEventEx* pEvent;
    IVideoWindow* pVidWin;
    IMediaSeeking* pSeek;
};
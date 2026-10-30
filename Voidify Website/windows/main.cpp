#include <windows.h>
#include <wrl.h>
#include <WebView2.h>
#include <string>
using Microsoft::WRL::ComPtr;
static HWND windowHandle = nullptr;
static ComPtr<ICoreWebView2Controller> controller;
static ComPtr<ICoreWebView2> webview;
void Resize() {
    if (!controller) return;
    RECT bounds;
    GetClientRect(windowHandle, &bounds);
    controller->put_Bounds(bounds);
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_SIZE) { Resize(); return 0; }
    if (msg == WM_DESTROY) { PostQuitMessage(0); return 0; }
    return DefWindowProcW(hwnd, msg, wp, lp);
}
int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int show) {
    WNDCLASSW cls{};
    cls.lpfnWndProc = WindowProc;
    cls.hInstance = instance;
    cls.lpszClassName = L"VoidifyWindow";
    cls.hCursor = LoadCursor(nullptr, IDC_ARROW);
    RegisterClassW(&cls);
    windowHandle = CreateWindowW(cls.lpszClassName, L"Voidify", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 800, nullptr, nullptr, instance, nullptr);
    ShowWindow(windowHandle, show);
    CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr,
        Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
                if (FAILED(result) || !env) return result;
                env->CreateCoreWebView2Controller(windowHandle,
                    Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                        [](HRESULT hr, ICoreWebView2Controller* created) -> HRESULT {
                            if (FAILED(hr) || !created) return hr;
                            controller = created;
                            controller->get_CoreWebView2(&webview);
                            Resize();
                            webview->Navigate(L"VOIDIFY_SITE_URL");
                            return S_OK;
                        }).Get());
                return S_OK;
            }).Get());
    MSG message;
    while (GetMessageW(&message, nullptr, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }
    return 0;
}

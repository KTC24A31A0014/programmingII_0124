//ウィンドウ制御クラスの実装
#include "window.h"
#include "input.h"

namespace
{
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

[[nodiscard]] HRESULT window::create(HINSTANCE instance, int width, int height, std::string_view name) noexcept
{
	//ウィンドウの定義
	WNDCLASS wc{};
	wc.lpfnWndProc	 = WindowProc;
	wc.hInstance	 = instance;
	wc.lpszClassName = name.data();
	wc.hCursor		 = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//ウィンドウクラスの登録
	RegisterClass(&wc);

	//ウィンドウの作成
	handle_ = CreateWindow(wc.lpszClassName, wc.lpszClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, instance, nullptr);

	if (!handle_)
	{
		return E_FAIL;
	}

	//ウィンドウの表示
	ShowWindow(handle_, SW_SHOW);

	//ウィンドウの更新
	UpdateWindow(handle_);

	//ウィンドウのサイズ保存
	width_	= width;
	height_ = height;

	return S_OK;
}

[[nodiscard]] bool window::messageLoop() const noexcept
{
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;	//WM_QUITメッセージが来たらループを抜ける
		}

		//メッセージ処理 
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		//キー情報の取得
		static byte keyState[256]{};
		if (GetKeyboardState(keyState))
		{
			//キー情報取得に成功したら、input クラスに情報を渡す
			input::instance().updateKeyState(keyState);
		}
	}

	return true;
}

[[nodiscard]] HWND window::handle() const noexcept
{
	return handle_;
}

[[nodiscard]] std::pair<int, int> window::size() const noexcept
{
	return { width_, height_ };
}
// ウィンドウ制御クラス
#pragma once

#include <windows.h>
#include <string>

using namespace std;

class window final
{
	public:
		window() = default;
		~window() = default;

    [[nodiscard]] HRESULT create(HINSTANCE instance, int width, int height, string_view name) noexcept;

	[[nodiscard]] bool messageLoop() const noexcept;

	[[nodiscard]] HWND handle() const noexcept;

	[[nodiscard]] pair <int, int> size() const noexcept;


	private:
		HWND handle_{};
		int width_{};
		int height_{};
};
//入力処理を担当

#pragma once

#include <Windows.h>
#include <cstdint>
#include <array>

class input final
{
	public:
		static input& instance() noexcept
		{
			static input instance;
			return instance;
		}

		//入力されていればtrue
		[[nodiscard]] bool getKey(uint16_t sKey) const noexcept;

		//入力したらtrue
		[[nodiscard]] bool getTrigger(uint16_t sKey) const noexcept;

		//ハードから設定されたキー情報配列のポインタ
		void updateKeyState(void* pState) noexcept;

		void upadatePrevKeyState() noexcept;

	private:
		//シングルトンパターンにするため、コンストラクタとデストラクタをprivateにする
		input() = default;
		~input() = default;

		input(const input& r)				= delete;
		input& operator= (const input& r)	= delete;
		input(input&& r)					= delete;
		input& operator = (input&& r)		= delete;

		std::array<byte, 256> keyState_{};		//ハードから設定されたキー情報配列
		std::array<byte, 256> prevKeyState_{};	//ハードから設定されたキー情報配列

};


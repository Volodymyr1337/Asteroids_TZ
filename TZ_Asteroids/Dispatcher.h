#pragma once
#include "vec2.h"
template <typename... Args>
struct event {
	using callable_type = std::function<void(Args...)>;

	event& operator=(std::nullptr_t) {
		m_Listeners.clear();
		return *this;
	}

	template <typename FFwd>
	event& operator=(FFwd&& fn) {
		*this = nullptr;
		*this += std::forward<FFwd>(fn);
		return *this;
	}

	template <typename FFwd,
		typename = std::enable_if_t<std::is_convertible_v<FFwd, callable_type>>>
		event& operator+=(FFwd&& fn) {
		m_Listeners.push_back(std::forward<FFwd>(fn));
		return *this;
	}

	template <typename... ArgsFwd>
	void operator()(ArgsFwd&&... args) {
		for (auto& l : m_Listeners) {
			l(args...);
		}
	}

private:
	std::vector<callable_type> m_Listeners;
};

class Dispatcher
{

public:
	static Dispatcher& Instance()
	{
		static Dispatcher _instance;
		return _instance;
	}
	event<FRMouseButton, bool> onMouseButtonClick = event<FRMouseButton, bool>();
	event<int> onAsteroidDestroyed = event<int>();
	event<FRKey> onKeyPressed = event<FRKey>();
	event<FRKey> onKeyReleased = event<FRKey>();
	event<vec2f> onMouseMove = event<vec2f>();

private:
	Dispatcher() {};
	~Dispatcher() {};

	Dispatcher(Dispatcher const&) = delete;
	Dispatcher& operator= (Dispatcher const&) = delete;

};


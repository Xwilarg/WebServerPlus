#ifndef WEBSERVER_HPP_
# define WEBSERVER_HPP_

# include <cpprest/http_listener.h>
# include <string>
# include <array>

namespace WebServer
{
	class WebServer final
	{
	public:
		WebServer(std::wstring &&ip, std::wstring &&port) noexcept;
		~WebServer() noexcept;

	private:
		void GetColors(web::http::http_request message) const noexcept;
		void UpdateColors(web::http::http_request message) noexcept;
		web::http::experimental::listener::http_listener _listenerGet;
		web::http::experimental::listener::http_listener _listenerUpdate;
		std::array<std::wstring, 100> _allcolors;
	};
}

#endif //! WEBSERVER_HPP_

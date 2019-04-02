#include "WebServer.hpp"

namespace WebServer
{
	WebServer::WebServer(std::wstring &&ip, std::wstring &&port) noexcept
		: _listener(L"http://" + ip + L":" + port), _allcolors(new std::wstring[100])
	{
		auto red = std::wstring(L"255000000");
		for (int i = 0; i < 100; i++)
		{
			_allcolors[i] = red;
		}
		_listener.support(web::http::methods::GET, std::bind(&WebServer::GetRequest, this, std::placeholders::_1));
		_listener.support(web::http::methods::POST, std::bind(&WebServer::PostRequest, this, std::placeholders::_1));
		_listener.open().wait();
	}

	WebServer::~WebServer() noexcept
	{
		delete[] _allcolors;
		_listener.close().wait();
	}

	void WebServer::GetRequest(web::http::http_request message) const noexcept
	{
		auto colors = web::json::value::array(100);
		for (int i = 0; i < 100; i++)
			colors.at(i) = web::json::value::string(_allcolors[i]);
		web::http::http_response response;
		response.set_status_code(web::http::status_codes::OK);
		response.set_body(colors);
		response.headers().add(L"Access-Control-Allow-Origin", "*");
		message.reply(response);
	}

	void WebServer::PostRequest(web::http::http_request message) const noexcept
	{
		auto body = message.extract_string().get();
		std::wstring str(body.begin(), body.end());
		size_t pos;
		pos = str.find(L";");
		int posX = std::stoi(str.substr(0, pos));
		str.erase(0, pos + 1);
		pos = str.find(L";");
		int posY = std::stoi(str.substr(0, pos));
		str.erase(0, pos + 1);
		_allcolors[posX * 10 + posY] = str;
		GetRequest(message);
	}
}
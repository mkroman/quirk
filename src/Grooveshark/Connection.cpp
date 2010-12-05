/*
 * Copyright (C) 2010 Mikkel Kroman <mk@maero.dk>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <json/json.h>
#include <iostream>
#include <sstream>

#include "Connection.h"

Grooveshark::Connection::Connection() :
	request()
{
	cURLpp::initialize(CURL_GLOBAL_ALL);
	request.setOpt<cURLpp::Options::WriteStream>(&buffer);
#if CURL_VERBOSE == TRUE
	request.setOpt<cURLpp::Options::Verbose>(true);
#endif
}

Grooveshark::Connection::~Connection()
{
	cURLpp::terminate();
}

void Grooveshark::Connection::initiateSession()
{
	processPHPCookie();
	fetchSessionToken();
}

void Grooveshark::Connection::fetchSessionToken()
{
	gsDebug("Fetching session token...");

	try {
		request.setOpt<cURLpp::Options::Url>("https://cowbell.grooveshark.com/service.php");

		std::list<std::string> header;
		header.push_back("Content-Type: application/json");

		request.setOpt<cURLpp::Options::HttpHeader>(header);

		// Start constructing the json data
		Json::Value jheaders;
		jheaders["client"] = "gslite";
		jheaders["clientRevision"] = GROOVESHARK_REVISION;

		Json::Value jparams;
		jparams["secretKey"] = "fem fire tre to en";

		Json::Value jlist;
		jlist["method"] = "getCommunicationToken";
		jlist["header"] = jheaders;
		jlist["parameters"] = jparams;

		Json::FastWriter writer;
		request.setOpt<cURLpp::Options::PostFields>(writer.write(jlist));

		request.perform();

	} catch (cURLpp::LogicError& exception) {
		gsError(exception.what());
	} catch (cURLpp::RuntimeError& exception) {
		gsError(exception.what());
	}
}

void Grooveshark::Connection::processPHPCookie()
{
	gsDebug("Storing PHP cookie...");

	try {
		request.setOpt<cURLpp::Options::Url>("http://listen.grooveshark.com");
		request.setOpt<cURLpp::Options::CookieFile>("grooveshark.cookie");
		request.perform();
	} catch (cURLpp::LogicError& exception) {
		gsError(exception.what());
	} catch (cURLpp::RuntimeError& exception) {
		gsError(exception.what());
	}

	gsDebug("Storage complete...");
}

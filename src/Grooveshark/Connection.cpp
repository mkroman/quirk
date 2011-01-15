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

#include "Grooveshark/Connection.h"

Grooveshark::Connection::Connection()
{
	curl_global_init(CURL_GLOBAL_ALL);
}

Grooveshark::Connection::~Connection()
{
	curl_global_cleanup(CURL_GLOBAL_ALL);
}

void Grooveshark::Connection::initiateSession()
{
	processPHPCookie();
	fetchSessionToken();
}

void Grooveshark::Connection::fetchSessionToken()
{
	gsDebug("Fetching session token...");
	
	
}

std::string Grooveshark::Connection::buildJSON(const std::string& method, Json::Value& params)
{
	Json::FastWriter writer;
	Json::Value jheaders, jlist;

	jheaders["client"] = "gslite";
	jheaders["clientRevision"] = GROOVESHARK_REVISION;

	jlist["method"] = method;
	jlist["header"] = jheaders;
	jlist["parameters"] = params;

	return writer.write(jlist);
}

void Grooveshark::Connection::processPHPCookie()
{
	gsDebug("Storing PHP cookie...");
	
	
}

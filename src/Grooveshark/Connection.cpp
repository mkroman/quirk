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

#include <curl/curl.h>
#include <json/json.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "Grooveshark/Connection.h"

Grooveshark::Connection::Connection() :
	curl(curl_easy_init())
{
	curl_global_init(CURL_GLOBAL_ALL);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
}

Grooveshark::Connection::~Connection()
{
	curl_easy_cleanup(curl);
	curl_global_cleanup();
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

	CURLcode response;
	
	curl_easy_setopt(curl, CURLOPT_URL, "http://listen.grooveshark.com/");
	response = curl_easy_perform(curl);

	struct curl_slist *cookies;
	curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);

	curl_cookie* cookie = curl_parse_cookie(&cookies[0]);

	printf("%s = %s\n", cookie->key, cookie->value);

	free(cookie);

	curl_slist_free_all(cookies);
}

curl_cookie* curl_parse_cookie(curl_slist* slist)
{
	curl_cookie* cookie;
	char *token;
	int i;

	i = 0;
	cookie = (curl_cookie*)malloc(sizeof(cookie));
	token = strtok(slist->data, "\t");

	while (token)
	{
		if (i == 5)
			cookie->key = token;
		else if (i == 6)
			cookie->value = token;

		i++;
		token = strtok(NULL, "\t");
	}

	free(token);
	return cookie;
}

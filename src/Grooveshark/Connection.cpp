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

#include <iostream>
#include <sstream>

#include "Connection.h"

Grooveshark::Connection::Connection() :
	cleanup(),
	request()
{
	// …
}

Grooveshark::Connection::~Connection()
{
	// …
}

void Grooveshark::Connection::initiateSession()
{
	processPHPCookie();
}

void Grooveshark::Connection::processPHPCookie()
{
	std::ostringstream buffer;

	gsDebug("Processing PHP cookie...");

	try {
		request.setOpt<cURLpp::Options::Url>("http://listen.grooveshark.com");
		request.setOpt<cURLpp::Options::WriteStream>(&buffer);
		request.perform();

		// Get the PHP Session cookie here..

	} catch (cURLpp::LogicError& exception) {
		gsError(exception.what());
	} catch (cURLpp::RuntimeError& exception) {
		gsError(exception.what());
	}

	gsDebug("Processing complete...");
}

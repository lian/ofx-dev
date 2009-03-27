#ifndef _SIMPLE_WEB_SCRAPER
#define _SIMPLE_WEB_SCRAPER


// http stuff ------------------------------------------
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;

// image stuff ---------------------------------------

#include "Poco/URIStreamOpener.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include <memory>
#include <iostream>

using Poco::URIStreamOpener;
using Poco::Net::HTTPStreamFactory;



// event stuff -------------------------------------
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"

using Poco::BasicEvent;
using Poco::Delegate;


#include "ofMain.h"
#define OF_ADDON_USING_OFXTHREAD
#include "ofAddons.h"

#define		TEXT_REQUEST 0
#define		STREAM_REQUEST 1

static bool factoryLoaded = false;

class StreamEventArgs {
	
	public:
		unsigned char *  buff;
		int bytesToRead;

};

class SimpleWebScraper : public ofxThread  {

    public:

        SimpleWebScraper();

        void getText(string url_);
		void getStreamThreaded(string url_);
		
		// testing! -----
		void getStreamUnthreaded(string url_);
		
		// threading -----------------------------------------------
		void threadedFunction();
        void start();
        void stop();

        // poco event stuff ----------------------------------------
		BasicEvent<string>				textReady;
		BasicEvent<StreamEventArgs>		unthreadedStreamReady;
		BasicEvent<StreamEventArgs>		threadedStreamReady;
		

		void notifyTextReceived(string response);
		void notifyUnthreadedStreamReceived( const StreamEventArgs args_);
		void notifyThreadedStreamReceived( const StreamEventArgs args_);
		
		
    private:
		
		// perform the requests on the thread
		void handleTextRequest(string url_);
		void handleStreamRequest(string url_);
        
		string			url;
        string			response;        
		bool			bResponseReady;		
		int				requestType;		
		StreamEventArgs args;


};

#endif

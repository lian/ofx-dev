#include "SimpleWebScraper.h"


SimpleWebScraper::SimpleWebScraper() {
	
}

void SimpleWebScraper::getText(string url_) {
    cout << "getText " << endl;

    url = url_;
	requestType = TEXT_REQUEST;
	start();
}

void SimpleWebScraper::getStreamUnthreaded(string url_) {
    cout << "getStreamUnthreaded " << endl;
	
	url	= url_;

	if(!factoryLoaded){
		HTTPStreamFactory::registerFactory();
		factoryLoaded = true;
	}
	
	string str;
	
	try {
		//specify out url and open stream
		URI uri(url_);      
		std::auto_ptr<std::istream> pStr(URIStreamOpener::defaultOpener().open(uri));
		//copy to our string
		StreamCopier::copyToString(*pStr.get(), str);
	} catch (Exception& exc) {
        cerr << exc.displayText() << std::endl;

    }	
	
	//figure out how many bytes the image is and allocate
	int bytesToRead = str.size();
	unsigned char buff[bytesToRead];

	memset(buff, 0, bytesToRead);

	for(int i = 0; i < bytesToRead; i++){
		buff[i] = str[i];
	}
	
	args.buff = buff;
	args.bytesToRead = bytesToRead;
	
	notifyUnthreadedStreamReceived(args);
	
}

void SimpleWebScraper::getStreamThreaded(string url_) {
    cout << "getStreamThreaded " << endl;

	args.buff			= NULL;
	args.bytesToRead	= NULL;
    url					= url_;
	requestType			= STREAM_REQUEST;
	
	if(!factoryLoaded){
		HTTPStreamFactory::registerFactory();
		factoryLoaded = true;
	}
	
    start();
}



void SimpleWebScraper::start() {
     if (isThreadRunning() == false){
        bResponseReady = false;
        startThread(false, false);   // blocking, verbose
    }
}

void SimpleWebScraper::stop() {
    stopThread();
}

void SimpleWebScraper::threadedFunction() {

    switch (requestType) {
		
		case TEXT_REQUEST: 
			handleTextRequest(url);
			notifyTextReceived(response);
			break;
		
		case STREAM_REQUEST: 
			handleStreamRequest(url); 
			notifyThreadedStreamReceived(args);
			break;
	}
	
    stop();
    response.clear();
    bResponseReady = true;

}

void SimpleWebScraper::handleTextRequest(string url_) {
	
	try {
		URI uri(url_);
        string path(uri.getPathAndQuery());
        if (path.empty()) path = "/";

        HTTPClientSession session(uri.getHost(), uri.getPort());
        HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
        session.sendRequest(req);

        HTTPResponse res; 
        std::istream& rs = session.receiveResponse(res);
        std::cout << res.getStatus() << " " << res.getReason() << std::endl;

        StreamCopier::copyToString(rs, response);
	} catch (Exception& exc) {
        cerr << exc.displayText() << std::endl;
    }		
	
}

void SimpleWebScraper::handleStreamRequest(string url_) {
	
	string str;
	
	try {
		//specify out url and open stream
		URI uri(url_);      
		std::auto_ptr<std::istream> pStr(URIStreamOpener::defaultOpener().open(uri));
		//copy to our string
		StreamCopier::copyToString(*pStr.get(), str);
	} catch (Exception& exc) {
        cerr << exc.displayText() << std::endl;

    }	
	
	//figure out how many bytes the image is and allocate
	int bytesToRead = str.size();
	unsigned char * buff = new unsigned char [bytesToRead];

	memset(buff, 0, bytesToRead);

	for(int i = 0; i < bytesToRead; i++){
		buff[i] = str[i];
	}
	
	args.buff			= buff;
	args.bytesToRead	= bytesToRead;
}	



void SimpleWebScraper::notifyTextReceived (string response) {
	textReady.notify(this, response);
}
void SimpleWebScraper::notifyUnthreadedStreamReceived (StreamEventArgs args) {
	unthreadedStreamReady.notify(this, args);
}

void SimpleWebScraper::notifyThreadedStreamReceived (StreamEventArgs args) {
	threadedStreamReady.notify(this, args);
}
       



//
//  CMTypes.h
//  Cumulus
//
//  Created by John Clayton on 8/20/11.
//  Copyright (c) 2011 Fivesquare Software, LLC. All rights reserved.
//

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of Fivesquare Software nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE ICONFACTORY BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

@class CMRequest;
@class CMResponse;

/** A block that is called after the request is marshalled but before the connection is started. You can use this block to do things like modify request headers or cause a request to abort. 
 *  @returns YES if the request should run.
 *  @note Runs on the main thread.
 */
typedef BOOL (^CMPreflightBlock)(CMRequest *request);

/** A block that is called once when a request begins, and subsequently whenever a request receives more data from the server. 
 *
 * @param progressInfo is an CMProgressInfo instance that responds to the following keys:
 *   - kCumulusProgressInfoKeyURL (URL)
 *   - kCumulusProgressInfoKeyProgress (progress)
 */
typedef void (^CMProgressBlock)(id progressInfo);

/** A block that is called once a request has processed its response using any coders that were applicable to the response mime-type. You can use this block to further process the result. The return value overwrites the current result for the request. The response is provided so you can determine whether there were any errors in your post-processing logic. */
typedef id (^CMPostProcessorBlock)(CMResponse *response, id result);

/** A block that is called once all request processing is complete. This block is always dispatched on the main queue so it is safe to do things like update your UI from here. */
typedef void (^CMCompletionBlock)(CMResponse *response);

/** A block that runs whenever a request is aborted. */
typedef void (^CMAbortBlock)(CMRequest *request);

typedef enum {
	CMContentTypeNone
	, CMContentTypeJSON
	, CMContentTypeXML
	, CMContentTypeHTML
	, CMContentTypeText
	, CMContentTypePNG
} CMContentType;

/** A content range represents an HTTP content range by setting location to the initial byte, length to the difference between the first byte and last byte and contentLength to the total length of the content for which a range is being requested. */
typedef struct {
    long long location;
    long long length;
	long long contentLength;
} CMContentRange;

static inline CMContentRange CMContentRangeMake(long long loc, long long len, long long clen) {
    CMContentRange range;
    range.location = loc;
    range.length = len;
	range.contentLength = clen;
    return range;
}

static inline long long CMContentRangeLastByte(CMContentRange range) {
	return range.location+range.length-1; // byte ranges are 0 indexed
}



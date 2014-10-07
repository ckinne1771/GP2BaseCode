//
//  Vertex.h
//  GP2BaseCode
//
//  Created by Brian on 28/09/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#ifndef Vertex_h
#define Vertex_h

struct Vertex
{
    float x,y,z;
	float tu, tv;
	float r,g,b,a;
};

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#endif

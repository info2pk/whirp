/*
 *  GeometryOBJReader.h
 *  WhirlyGlobeLib
 *
 *  Created by Steve Gifford on 11/25/14.
 *  Copyright 2012-2014 mousebird consulting
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#import "GeometryManager.h"

namespace WhirlyKit
{
    
// Geometry model parser for Wavefront OBJ format
class GeometryModelOBJ
{
public:
    // Parse file
    bool parse(FILE *fp);
    
    // Convert to raw geometry objects
    void toRawGeometry(std::vector<GeometryRaw> &rawGeom);
    
    // Vertices point to a vertex and optionally a tex coordinate and normal
    class Vertex
    {
    public:
        Vertex() : vert(-1), texCoord(-1), norm(-1) { }
        int vert;
        int texCoord;
        int norm;
    };

    // Face is just a collection of vertices
    class Face
    {
    public:
        std::vector<Vertex> verts;
    };

    class Material
    {
    public:
        bool operator < (const Material &that) const
        {
            return textureName < that.textureName;
        }
            
        std::string name;
        std::string textureName;
    };

    // Group is currently just a collection of faces
    class Group
    {
    public:
        Material *mat;
        std::string name;
        std::vector<Face> faces;
    };
    
    std::vector<Group> groups;
    std::vector<Point3d> verts;
    std::vector<Point2d> texCoords;
    std::vector<Point3d> norms;
    std::vector<Material> materials;
};

}

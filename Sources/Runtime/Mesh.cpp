#include "Mesh.h"
#include "Vector3.h"
#include "Color.h"
#include "GL.h"
#include<vector>

namespace BDXKEngine {
	Mesh* Mesh::CreateCube()
	{
		Mesh* mesh = new Mesh();
		mesh->vertices = {
		{{ -0.5f, -0.5f, -0.5f},{},{}, {0,0,0}},
		{{ -0.5f, -0.5f, 0.5f },{},{}, {0,0,1}},
		{{ 0.5f, -0.5f, 0.5f },{},{}, {0,0,1}},
		{{ 0.5f,-0.5f,-0.5f },{},{}, {1,0,0}},
		{{ -0.5f,0.5f,-0.5f },{},{}, {0,1,0}},
		{{ -0.5f,0.5f,0.5f },{},{}, {0,0,1}},
		{{0.5f,0.5f, 0.5f },{},{}, {0,0,1}},
		{{0.5f,0.5f, -0.5f },{},{}, {1,1,0}}
		};
		mesh->triangles = {//ǰ����������
			0,4,7,
			0,7,3,
			2,6,5,
			2,5,1,
			1,5,4,
			1,4,0,
			3,7,6,
			3,6,2,
			4,5,6,
			4,6,7,
			0,3,2,
			0,2,1
		};
		mesh->UploadMeshData();

		return mesh;
	}

	Mesh::Mesh()
	{

	}

	Mesh::Mesh(StaticMesh staticMesh)
	{
		SetTriangles(staticMesh.triangles);
		SetPositions(staticMesh.positions);
		SetNormals(staticMesh.normals);
		SetUVs(staticMesh.uvs);
		SetColors(staticMesh.colors);

		UploadMeshData();
	}
}
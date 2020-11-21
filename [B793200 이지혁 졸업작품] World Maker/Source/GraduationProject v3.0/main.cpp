////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"
#include <fstream>

bool windowActivate = true;

typedef struct
{
	float x, y, z;
}VertexType;

typedef struct
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
}FaceType;

bool ReadFileCounts(char*, int&, int&, int&, int&);
bool LoadDataStructures(char*, int, int, int, int, int&, int&, int);
//bool ReadTxtFileCounts(char*, int&);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;
	
	int cntObj = CURRENTMODELNUM;
	int cntPoly = 58716;
	
	int vertexCount, textureCount, normalCount, faceCount;

	/*char filename[MAXMODELNUM][256] = { "Floor.obj", "LWall.obj", "RWall.obj", "Sphere.obj"
									 "PadMe.obj", "PadOpponent.obj"};

	for (int i = 0; i < MAXMODELNUM; i++)
	{
		result = ReadFileCounts(filename[i], vertexCount, textureCount, normalCount, faceCount);
		cntObj += 1;
		cntPoly += faceCount * 3;
	}*/

	// Create the system object.
	System = new SystemClass;
	if(!System)
	{
		return 0;
	}

	// Initialize and run the system object.
	result = System->Initialize(cntObj, cntPoly);
	if(result)
	{
		System->Run();
	}

	// Shutdown and release the system object.
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}

//bool ReadTxtFileCounts(char* filename, int& cntPoly)
//{
//	ifstream fin;
//	char input;
//	int vertexIndex;
//	// ������ ���� ��.
//	fin.open(filename);
//
//	// ���� ���⿡ �����ߴ��� Ȯ���մϴ�.
//	if (fin.fail() == true)
//	{
//		return false;
//	}
//
//	//14��°���� ����
//	fin.get(input);
//}


bool ReadFileCounts(char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount)
{
	ifstream fin;
	char input;


	// ī��Ʈ�� �ʱ�ȭ�մϴ�.
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	// ������ ���� ��.
	fin.open(filename);

	// ���� ���⿡ �����ߴ��� Ȯ���մϴ�.
	if (fin.fail() == true)
	{
		return false;
	}

	// ���Ͽ��� ���� ���� ������ ���� ���� �� ������ ��� �н��ϴ�.
	fin.get(input);
	while (!fin.eof())
	{
		// ������ 'v'�� �����ϸ� ������, �ؽ�ó ��ǥ �Ǵ� ���� ���͸� ����մϴ�.
		if (input == 'v')
		{
			fin.get(input);
			if (input == ' ') { vertexCount++; }
			if (input == 't') { textureCount++; }
			if (input == 'n') { normalCount++; }
		}

		// ������ 'f'�� �����ϸ�� ���� ������ŵ�ϴ�.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ') { faceCount++; }
		}

		// �׷��� ������ ������ ���� �н��ϴ�.
		while (input != '\n')
		{
			fin.get(input);
		}

		// ���� ���� ���� �κ��� �б� �����Ѵ�.
		fin.get(input);
	}

	// ������ �ݽ��ϴ�.
	fin.close();

	return true;
}


bool LoadDataStructures(char* filename, int vertexCount, int textureCount, int normalCount, int faceCount, int &cntObj, int &cntPoly, int num)
{
	VertexType *vertices, *texcoords, *normals;
	FaceType *faces;
	ifstream fin;
	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
	char input, input2;
	ofstream fout;
	char name[256];
	strcpy_s(name, filename);
	int len = strlen(name);
	name[len - 4] = '\0';
	strcat_s(name, ".txt");

	// �� ���� ������ ������ �ʱ�ȭ�մϴ�.
	vertices = new VertexType[vertexCount];
	if (!vertices)
	{
		return false;
	}

	texcoords = new VertexType[textureCount];
	if (!texcoords)
	{
		return false;
	}

	normals = new VertexType[normalCount];
	if (!normals)
	{
		return false;
	}

	faces = new FaceType[faceCount];
	if (!faces)
	{
		return false;
	}

	// �ε����� �ʱ�ȭ�մϴ�.
	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	// ������ ���ϴ�.
	fin.open(filename);

	// ���� ���⿡ �����ߴ��� Ȯ���Ͻʽÿ�.
	if (fin.fail() == true)
	{
		return false;
	}

	// ����, �ؽ�ó ��ǥ �� ������ ������ ������ �о���Դϴ�.
	// �߿� : Maya�� ������ ��ǥ�踦 ����ϱ� ������ �޼� ��ǥ��� ��ȯ�Ѵ�.
	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);

			// ������ �н��ϴ�.
			if (input == ' ')
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;

				// Z ������ ������ �޼� �ý������� �ٲ۴�.
				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++;
			}

			// �ؽ�ó uv ��ǥ�� �н��ϴ�.
			if (input == 't')
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;

				// V �ؽ�ó ��ǥ�� �޼� �ý������� ������ŵ�ϴ�.
				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++;
			}

			// ������ �н��ϴ�.
			if (input == 'n')
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;

				// Z ������ �������� �޼� �ý������� �����մϴ�.
				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++;
			}
		}

		// ǥ���� �д´�.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				// ������ �ý��ۿ��� �޼� �ý������� ��ȯ�ϱ� ���� ǥ�� �����͸� �Ųٷ� �н��ϴ�.
				fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
					>> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
					>> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
				faceIndex++;
			}
		}

		// ������ ���� �н��ϴ�.
		while (input != '\n')
		{
			fin.get(input);
			if (fin.eof()) break;
		}

		// ���� ���� ���� �κ��� �б� �����Ѵ�.
		fin.get(input);
	}

	// ������ �ݽ��ϴ�.
	fin.close();

	// ��� ������ ���ϴ�.
	fout.open(name);
	cntObj++;

	// �� ���Ŀ��� ����ϴ� ���� ����� �ۼ��մϴ�.
	fout << "Vertex Count: " << (faceCount * 3) << endl;
	fout << endl;
	fout << "Data:" << endl;
	fout << endl;
	cntPoly += (faceCount * 3);

	// ���� ������ �ݺ��ϰ� ������ �� �������� ����մϴ�.
	for (int i = 0; i < faceIndex; i++)
	{
		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].tIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;
	}

	// ��� ������ �ݴ´�.
	fout.close();

	// �� ���� ������ ������ �����Ѵ�.
	if (vertices)
	{
		delete[] vertices;
		vertices = 0;
	}
	if (texcoords)
	{
		delete[] texcoords;
		texcoords = 0;
	}
	if (normals)
	{
		delete[] normals;
		normals = 0;
	}
	if (faces)
	{
		delete[] faces;
		faces = 0;
	}

	return true;
}
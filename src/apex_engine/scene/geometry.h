#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "spatial.h"

#include "../rendering/shader.h"
#include "../rendering/mesh.h"
#include "../rendering/mesh_util.h"
#include "../rendering/material.h"
#include "../rendering/enums.h"

#include "../math/boundingbox.h"

#include <memory>
using std::shared_ptr;

namespace apex
{
	class RenderManager;

	class Camera;

	class Geometry : public Spatial
	{
	private:
		static int geom_count;

		RenderManager *renderMgr; // Contains a list of all geometry that can be rendered (attached to the root node)

		shared_ptr<Shader> shader;
		shared_ptr<Mesh> mesh;

		Material material;

		RenderBucket bucket;

		BoundingBox localBoundingBox, globalBoundingBox;
		bool localBoundingBoxCreated, globalBoundingBoxCreated;

		Vector3f tmpMin, tmpMax;

		void updateGlobalBoundingBox();

		void updateLocalBoundingBox();
	public:
		Geometry();

		Geometry(string name);

		Geometry(shared_ptr<Mesh> mesh);

		Geometry(shared_ptr<Mesh> mesh, string name);

		~Geometry();

		void update(RenderManager *renderMgr, const float dt);

		void render(Camera &cam);

		void updateParents();

		Mesh *getMesh()
		{
			return this->mesh.get();
		}

		void setMesh(shared_ptr<Mesh> mesh)
		{
			this->mesh = mesh;
			this->setNeedsLocalBoundingBoxUpdate();
			this->setNeedsGlobalBoundingBoxUpdate();

			Spatial *par = this->getParent();

			while (par != 0)
			{

				par->setNeedsGlobalBoundingBoxUpdate();
				par->setNeedsLocalBoundingBoxUpdate();
				par = par->getParent();
				
			}
		}

		Material &getMaterial()
		{
			return material;
		}

		void setMaterial(Material material)
		{
			this->material = material;
		}

		shared_ptr<Shader> getShader()
		{
			return shader;
		}

		void setShader(shared_ptr<Shader> shader)
		{
			this->shader = shader;
		}

		RenderBucket getBucket()
		{
			return bucket;
		}

		void setBucket(RenderBucket bucket);

		void setNeedsTransformUpdate()
		{
			Spatial::setNeedsTransformUpdate();
		}

		BoundingBox &getGlobalBoundingBox();

		BoundingBox &getLocalBoundingBox();
	};
}
#endif
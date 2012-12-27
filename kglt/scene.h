#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <sigc++/sigc++.h>
#include <boost/any.hpp>
#include <boost/thread/mutex.hpp>

#include <stdexcept>
#include <map>

#include "kazbase/list_utils.h"

#include "types.h"
#include "object.h"
#include "mesh.h"
#include "camera.h"
#include "renderer.h"
#include "texture.h"
#include "shader.h"
#include "viewport.h"
#include "material.h"
#include "light.h"
#include "scene_group.h"
#include "mesh.h"
#include "entity.h"

#include "pipeline.h"

#include "generic/visitor.h"
#include "generic/manager.h"

namespace kglt {

class WindowBase;
class UI;

typedef generic::TemplatedManager<Scene, Mesh, MeshID> MeshManager;
typedef generic::TemplatedManager<Scene, ShaderProgram, ShaderID> ShaderManager;
typedef generic::TemplatedManager<Scene, Material, MaterialID> MaterialManager;
typedef generic::TemplatedManager<Scene, Texture, TextureID> TextureManager;

class ResourceManager:
    public MeshManager,
    public ShaderManager,
    public MaterialManager,
    public TextureManager {

public:
    ResourceManager(ResourceManager* parent=nullptr):
        parent_(parent) {
        ShaderManager::signal_post_create().connect(sigc::mem_fun(this, &ResourceManager::post_create_shader_callback));
    }

    MeshID new_mesh();
    Mesh& mesh(MeshID m);
    bool has_mesh(MeshID m) const;
    const Mesh& mesh(MeshID m) const;
    void delete_mesh(MeshID mid);

    TextureID new_texture();
    Texture& texture(TextureID t);
    void delete_texture(TextureID tid);

    ShaderID new_shader();
    ShaderProgram& shader(ShaderID s);
    void delete_shader(ShaderID s);

    MaterialID new_material(MaterialID clone_from=MaterialID());
    Material& material(MaterialID material);
    void delete_material(MaterialID m);


    std::pair<ShaderID, bool> find_shader(const std::string& name);
    void post_create_shader_callback(ShaderProgram& obj, ShaderID id) {
        shader_lookup_[obj.name()] = id;
    }

    ResourceManager& parent() {
        assert(parent_);
        return *parent_;
    }
private:
    ResourceManager* parent_;

    std::map<std::string, ShaderID> shader_lookup_;
};

class Scene :
    public Object,
    public Loadable,
    public ResourceManager,
    public generic::TemplatedManager<Scene, Camera, CameraID>,
    public generic::TemplatedManager<Scene, Light, LightID>,
    public generic::TemplatedManager<Scene, SceneGroup, SceneGroupID>,
    public generic::TemplatedManager<Scene, Entity, EntityID> {

public:
    void move(float x, float y, float z) {
        throw std::logic_error("You cannot move the scene");
    }

    Scene(WindowBase* window);
    ~Scene();

    SceneGroupID new_scene_group();
    SceneGroup& scene_group(SceneGroupID group=0);
    void delete_scene_group(SceneGroupID group);

    EntityID new_entity(MeshID mid=MeshID());
    EntityID new_entity(Object& parent, MeshID mid=MeshID());

    Entity& entity(EntityID e);
    bool has_entity(EntityID e) const;
    void delete_entity(EntityID e);

    CameraID new_camera();
    LightID new_light(Object* parent=nullptr, LightType type=LIGHT_TYPE_POINT);    

    Camera& camera(CameraID c = DefaultCameraID);
    Light& light(LightID light);

    void delete_camera(CameraID cid);
    void delete_light(LightID light_id);

    void init();
    void render();
    void update(double dt);

    WindowBase& window() { return *window_; }

    MeshID _mesh_id_from_mesh_ptr(Mesh* mesh);

    template<typename T, typename ID>
    void post_create_callback(T& obj, ID id) {
        obj.set_parent(this);
        obj._initialize(*this);
    }

    MaterialID default_material() const { return default_material_; }

    SceneGroupID default_scene_group() const { return default_scene_group_; }

    kglt::Colour ambient_light() const { return ambient_light_; }
    void set_ambient_light(const kglt::Colour& c) { ambient_light_ = c; }

    sigc::signal<void, EntityID>& signal_entity_created() { return signal_entity_created_; }
    sigc::signal<void, EntityID>& signal_entity_destroyed() { return signal_entity_destroyed_; }

    sigc::signal<void, LightID>& signal_light_created() { return signal_light_created_; }
    sigc::signal<void, LightID>& signal_light_destroyed() { return signal_light_destroyed_; }

    Pipeline& pipeline() { return *pipeline_; }
private:
    WindowBase* window_;

    CameraID default_camera_;
    SceneGroupID default_scene_group_;
    TextureID default_texture_;
    MaterialID default_material_;
    kglt::Colour ambient_light_;

    void initialize_defaults();

    Pipeline::ptr pipeline_;

    sigc::signal<void, EntityID> signal_entity_created_;
    sigc::signal<void, EntityID> signal_entity_destroyed_;

    sigc::signal<void, LightID> signal_light_created_;
    sigc::signal<void, LightID> signal_light_destroyed_;
};

}

#endif // SCENE_H_INCLUDED

#ifndef TEST_OBJ_LOADER_H
#define TEST_OBJ_LOADER_H

#include "kglt/loaders/obj_loader.h"

class OBJLoaderTest : public TestCase {
public:
    void set_up() {
        if(!window) {
            window = kglt::Window::create();
            window->set_logging_level(kglt::LOG_LEVEL_NONE);
        }

        //window->reset();
    }

    void test_face_parsing() {
        unicode line = "1//2";

        int32_t v, vn, vt;

        kglt::loaders::parse_face(line, v, vt, vn);

        assert_equal(0, v);
        assert_equal(-1, vt);
        assert_equal(1, vn);

        line = "1";

        kglt::loaders::parse_face(line, v, vt, vn);

        assert_equal(0, v);
        assert_equal(-1, vt);
        assert_equal(-1, vn);

        line = "1/2";

        kglt::loaders::parse_face(line, v, vt, vn);

        assert_equal(0, v);
        assert_equal(1, vt);
        assert_equal(-1, vn);

        line = "1/2/3";

        kglt::loaders::parse_face(line, v, vt, vn);

        assert_equal(0, v);
        assert_equal(1, vt);
        assert_equal(2, vn);

        line = "1//";

        kglt::loaders::parse_face(line, v, vt, vn);

        assert_equal(0, v);
        assert_equal(-1, vt);
        assert_equal(-1, vn);
    }

    void test_loading_without_texture_coords() {
        unicode path = os::path::join(os::path::dir_name(__FILE__), "test-data");
        window->resource_locator().add_search_path(path);

        //Shouldn't throw
        kglt::MeshID mid = window->scene().new_mesh_from_file("cube.obj");
    }
};

#endif // TEST_OBJ_LOADER_H

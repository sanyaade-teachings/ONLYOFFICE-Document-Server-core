core_mac {
    !use_v8:CONFIG += use_javascript_core
}
core_ios {
    CONFIG += use_javascript_core
}

INCLUDEPATH += $$PWD

use_javascript_core {
    QMAKE_OBJECTIVE_CFLAGS += -fobjc-arc -fobjc-weak

    LIBS += -framework Foundation
    LIBS += -framework JavaScriptCore

    DEFINES += JS_ENGINE_JAVASCRIPTCORE
}

defineTest(ADD_FILES_FOR_EMBEDDED_CLASS_HEADER) {
    header_path = $$absolute_path($$ARGS)
#    message(header_path: $$header_path)
    header_basename = $$basename(ARGS)
#    message(header_basename: $$header_basename)
    header_dir = $$dirname(header_path)
#    message(header_dir: $$header_dir)
    header_name_splitted = $$split(header_basename, .)
    header_basename_no_extension = $$first(header_name_splitted)
#    message(header_basename_no_extension: $$header_basename_no_extension)
    use_javascript_core {
        OBJECTIVE_SOURCES += $$header_dir/$$join(header_basename_no_extension,, jsc/jsc_, .mm)
    } else {
        SOURCES += $$header_dir/$$join(header_basename_no_extension,, v8/v8_, .cpp)
    }
    export(SOURCES)
    export(OBJECTIVE_SOURCES)
}

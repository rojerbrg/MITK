set( diffusion_module_dirs
      DiffusionCore
      FiberTracking
      Connectomics
      Quantification
)

foreach(diffusion_module_dir ${diffusion_module_dirs})
  add_subdirectory(${diffusion_module_dir})
endforeach()
add_subdirectory(MiniApps)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mitkDiffusionImagingConfigure.h.in ${CMAKE_CURRENT_BINARY_DIR}/DiffusionCore/mitkDiffusionImagingConfigure.h)

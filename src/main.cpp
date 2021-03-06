#include "engine.h"
#include <cstring>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  #include "direct.h"
#else
  #include <sys/stat.h>
#endif

Profiler profiler;
Params params;

int main(int argc, char *argv[]) {
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    _mkdir(params.outFolder.c_str());
  #else
    mkdir(params.outFolder.c_str(), 0777);
  #endif
  FLAGS_log_dir = params.outFolder;
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  ParticleType pType = ParticleType::SNOW;
  profiler.profStart(ProfType::INIT);
  params.setMaterial(pType);
  params.setOutput(true, true);
  params.log();
  Engine engine;
  engine.particleList_.type_ = pType;
  engine.particleList_.initToSquare();
  engine.initBoundary(3);
  engine.generateLevelset();

  profiler.profEnd(ProfType::INIT);
  
  for (int i = 0; i < params.stepSize; i++) {
#ifdef MPM_DEBUG
    LOG(INFO) << "Start loop " << i;
#endif
    engine.execOneStep();
	  // engine.writePositions(params.outFolder + "/" + "particles_" + paddingStr(std::to_string(i), '0', 4) + ".bin");
    engine.visualize(i);
    profiler.reportLoop(i);
    google::FlushLogFiles(google::GLOG_INFO);
  }
  profiler.report();
}
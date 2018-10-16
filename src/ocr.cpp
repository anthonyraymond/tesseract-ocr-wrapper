#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include "overridedrenderer.h"

// TODO : pour utiliser "stream" au lieu de fichier on peut se servir de cette solution: https://stackoverflow.com/a/23351463/2275818
/*const char* doOcr(char* imagePath)
{
  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
  if (api->Init(NULL, "fra", tesseract::OcrEngineMode::OEM_LSTM_ONLY)) {
      fprintf(stderr, "Could not initialize tesseract.\n");
      exit(1);
  }
  if (!api->SetVariable("classify_enable_learning", "0")) {
    fprintf(stderr, "Could not set option: classify_enable_learning\n");
  }
  if (!api->SetVariable("classify_enable_adaptive_matcher","0")) {
    fprintf(stderr, "Could not set option: classify_enable_adaptive_matcher\n");
  }

  std::string ocrStr = "";
  tesseract::PointerVector<tesseract::TessResultRenderer> renderers;
  renderers.push_back(new TessStringRenderer(&ocrStr));

  // Open input image with leptonica library
  if (!api->ProcessPages(imagePath, nullptr, 0, renderers[0])) {
    fprintf(stderr, "Error during OCR process.\n");
  }

  api->End();
  return ocrStr.c_str();
}*/

const char* doOcr(char* imagePath)
{
  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
  if (api->Init(NULL, "fra", tesseract::OcrEngineMode::OEM_LSTM_ONLY)) {
      fprintf(stderr, "Could not initialize tesseract.\n");
      exit(1);
  }
  if (!api->SetVariable("classify_enable_learning", "0")) {
    fprintf(stderr, "Could not set option: classify_enable_learning\n");
  }
  if (!api->SetVariable("classify_enable_adaptive_matcher","0")) {
    fprintf(stderr, "Could not set option: classify_enable_adaptive_matcher\n");
  }

  PIXA* pixa = pixaReadMultipageTiff(imagePath);
  if (pixa = leptonica::ERROR_PTR) {
    std::cout << "coucou" << std::endl;
  }

  return "";
}

int main(int argc, char** argv)
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <absolute path to image>" << std::endl;
    return 1;
  }
  char* imagePath = argv[1];
  const char* ocrOutput = doOcr(imagePath);

  std::cout << "from main" << ocrOutput << std::endl;
}

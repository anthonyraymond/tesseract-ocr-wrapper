#include <tesseract/baseapi.h>
#include <tesseract/renderer.h>
#include <memory>
#include <string>
#include "overridedrenderer.h"

TessStringRenderer::TessStringRenderer(std::string* str) : tesseract::TessResultRenderer("-", "txt") {
  // force the outputbase as "-", this makes the parent to use stdout as his output instead of a file, latter in this file we'll override the AppendString method to prevent stdout printing
  ocrStr = str;
}
void TessStringRenderer::AppendString(const char* s) {
  ocrStr->append(s);
}
bool TessStringRenderer::AddImageHandler(tesseract::TessBaseAPI* api) {
  const std::unique_ptr<const char[]> utf8(api->GetUTF8Text());
  if (utf8 == nullptr) {
    return false;
  }

  AppendString(utf8.get());

  const char* pageSeparator = api->GetStringVariable("page_separator");
  if (pageSeparator != nullptr && *pageSeparator != '\0') {
    AppendString(pageSeparator);
  }

  return true;
}

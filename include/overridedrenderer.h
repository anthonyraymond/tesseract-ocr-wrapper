#include <tesseract/renderer.h>
#include <string>

class TESS_API TessStringRenderer : public tesseract::TessResultRenderer {
  private:
    char mem_padding[7]; // This has no purpose execpt for padding (see Data structure alignment)
    std::string* ocrStr;
  public:
    explicit TessStringRenderer(std::string* ocrStr);

  protected:
    virtual bool AddImageHandler(tesseract::TessBaseAPI* api);
    void AppendString(const char* s);
};

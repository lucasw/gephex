#include "renderer.h"

#include "utils/ilogger.h"

int main()
{
  utils::AutoPtr<utils::ILogger> logger(0);
  renderer::Renderer r(logger);
}

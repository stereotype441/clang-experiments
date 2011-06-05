#include <string>

#include "llvm/Config/config.h"
#include "llvm/Support/raw_ostream.h"

#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/FileManager.h"

#include "clang/Lex/HeaderSearch.h"
#include "clang/Lex/Preprocessor.h"

#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Frontend/DiagnosticOptions.h"
#include "clang/Basic/TargetOptions.h"

using namespace clang;

int main()
{
  llvm::raw_fd_ostream out_stream(1, false);
  DiagnosticOptions diag_options;
  TextDiagnosticPrinter *diagClient = new TextDiagnosticPrinter(out_stream, diag_options);
  Diagnostic diags(diagClient);
  LangOptions opts;
  TargetOptions target_opts;
  target_opts.Triple = LLVM_HOSTTRIPLE;
  TargetInfo *target = TargetInfo::CreateTargetInfo(diags, target_opts);
  SourceManager sm(diags);
  FileManager fm;
  HeaderSearch headers(fm);
  Preprocessor pp(diags, opts, *target, sm, headers);
}

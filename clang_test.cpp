// Based on the tutorial at http://amnoid.de/tmp/clangtut/tut.html

#include <string>
#include <iostream>

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
#include "clang/Frontend/HeaderSearchOptions.h"
#include "clang/Frontend/Utils.h"
#include "clang/Frontend/PreprocessorOptions.h"
#include "clang/Frontend/FrontendOptions.h"
#include "clang/Basic/TargetOptions.h"

using namespace clang;
using namespace std;

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
  FileManager fm;
  SourceManager sm(diags);
  HeaderSearch headers(fm);
  Preprocessor pp(diags, opts, *target, sm, headers);
  PreprocessorOptions preprocessor_options;
  HeaderSearchOptions header_search_options;
  FrontendOptions frontend_options;
  InitializePreprocessor(
      pp, preprocessor_options, header_search_options, frontend_options);

  FileEntry const *file = fm.getFile("test.cpp");
  FileID main_file = sm.createMainFileID(file);
  diagClient->BeginSourceFile(opts, &pp);
  pp.EnterMainSourceFile();

  bool invalid = false;
  llvm::StringRef sr = sm.getBufferData(main_file, &invalid);
  (void) sr;

  Token tok;
  do {
    pp.Lex(tok);
    if (diags.hasErrorOccurred()) {
      break;
    }
    pp.DumpToken(tok);
    cerr << endl;
  } while (tok.isNot(tok::eof));
}

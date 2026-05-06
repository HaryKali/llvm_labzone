; ModuleID = 'Hello LLVM'
source_filename = "Hello LLVM"

@gStr = private constant [13 x i8] c"Hello,World\0A\00"

declare i32 @puts(ptr)

define i32 @main() {
entry:
  %call_puts = call i32 @puts(ptr @gStr)
  ret i32 1
}

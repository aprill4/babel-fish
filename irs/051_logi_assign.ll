@a9 = global i32 zeroinitializer
@b11 = global i32 zeroinitializer
define void @putint(i32 ) {
putint1:
  ret void
}
define void @putch(i32 ) {
putch3:
  ret void
}
define i32 @getint() {
getint4:
  ret i32 0
}
define i32 @getch() {
getch6:
  ret i32 0
}
define i32 @main() {
main12:
  %v13 = call i32 @getint()
  store i32 %v13, i32* @a9
  %v14 = call i32 @getint()
  store i32 %v14, i32* @b11
  %v15 = alloca i32
  store i32 zeroinitializer, i32* %v15
  %v22 = load i32, i32* @a9
  %v23 = load i32, i32* @b11
  %bool_24 = icmp eq i32 %v22, %v23
  %bool_26 = icmp ne i1 %bool_24, zeroinitializer
  br i1 %bool_26, label %l20, label %r21
if_true_entry17:
  store i32 1, i32* %v15
  br label %next_entry19
if_false_entry18:
  store i32 0, i32* %v15
  br label %next_entry19
next_entry19:
  %v34 = load i32, i32* %v15
  ret i32 %v34
l20:
  %v27 = load i32, i32* @a9
  %bool_29 = icmp ne i32 %v27, 3
  %bool_31 = icmp ne i1 %bool_29, zeroinitializer
  br i1 %bool_31, label %if_true_entry17, label %r21
r21:
  br label %if_false_entry18
}


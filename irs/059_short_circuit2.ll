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
define i32 @func(i32 ) {
func9:
  %v10 = alloca i32
  %v14 = load i32, i32* %v10
  %bool_16 = icmp sle i32 %v14, 50
  br i1 %bool_16, label %if_true_entry11, label %if_false_entry12
if_true_entry11:
  %v17 = load i32, i32* %v10
  call void @putint(i32 %v17)
  ret i32 1
if_false_entry12:
  %v20 = load i32, i32* %v10
  call void @putint(i32 %v20)
  ret i32 0
next_entry13:
  ret i32 zeroinitializer
}
define i32 @main() {
main24:
  %v25 = alloca i32
  store i32 zeroinitializer, i32* %v25
  %v33 = call i32 @func(i32 0)
  %bool_35 = icmp eq i32 %v33, 1
  %bool_37 = icmp ne i1 %bool_35, zeroinitializer
  br i1 %bool_37, label %l30, label %r31
if_true_entry27:
  store i32 0, i32* %v25
  br label %next_entry29
if_false_entry28:
  store i32 1, i32* %v25
  br label %next_entry29
next_entry29:
  %v62 = call i32 @func(i32 50)
  %bool_64 = icmp eq i32 %v62, 1
  %bool_66 = icmp ne i1 %bool_64, zeroinitializer
  br i1 %bool_66, label %l59, label %r60
l30:
  br label %if_true_entry27
r31:
  %v41 = call i32 @func(i32 50)
  %bool_43 = icmp eq i32 %v41, 1
  %bool_45 = icmp ne i1 %bool_43, zeroinitializer
  br i1 %bool_45, label %l38, label %r39
l38:
  %v47 = call i32 @func(i32 100)
  %bool_49 = icmp eq i32 %v47, 0
  %bool_51 = icmp ne i1 %bool_49, zeroinitializer
  br i1 %bool_51, label %if_true_entry27, label %r39
r39:
  br label %if_false_entry28
if_true_entry54:
  store i32 0, i32* %v25
  br label %next_entry56
if_false_entry55:
  store i32 1, i32* %v25
  br label %next_entry56
next_entry56:
  ret i32 0
l57:
  br label %if_true_entry54
r58:
  %v74 = call i32 @func(i32 1)
  %bool_76 = icmp eq i32 %v74, 1
  %bool_78 = icmp ne i1 %bool_76, zeroinitializer
  br i1 %bool_78, label %l57, label %if_false_entry55
l59:
  %v68 = call i32 @func(i32 40)
  %bool_70 = icmp eq i32 %v68, 1
  %bool_72 = icmp ne i1 %bool_70, zeroinitializer
  br i1 %bool_72, label %if_true_entry54, label %r60
r60:
  br label %if_false_entry55
}


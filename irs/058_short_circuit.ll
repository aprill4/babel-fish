@g10 = global i32 0
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
func12:
  %v13 = alloca i32
  %v14 = load i32, i32* @g10
  %v15 = load i32, i32* %v13
  %v16 = add nsw i32 %v14, %v15
  store i32 %v16, i32* @g10
  %v17 = load i32, i32* @g10
  call void @putint(i32 %v17)
  %v19 = load i32, i32* @g10
  ret i32 %v19
}
define i32 @main() {
main20:
  %v21 = alloca i32
  store i32 zeroinitializer, i32* %v21
  %v23 = call i32 @getint()
  store i32 %v23, i32* %v21
  %v29 = load i32, i32* %v21
  %bool_31 = icmp sgt i32 %v29, 10
  %bool_33 = icmp ne i1 %bool_31, zeroinitializer
  br i1 %bool_33, label %l27, label %r28
if_true_entry24:
  store i32 1, i32* %v21
  br label %next_entry26
if_false_entry25:
  store i32 0, i32* %v21
  br label %next_entry26
next_entry26:
  %v40 = call i32 @getint()
  store i32 %v40, i32* %v21
  %v46 = load i32, i32* %v21
  %bool_48 = icmp sgt i32 %v46, 11
  %bool_50 = icmp ne i1 %bool_48, zeroinitializer
  br i1 %bool_50, label %l44, label %r45
l27:
  %v34 = load i32, i32* %v21
  %v35 = call i32 @func(i32 %v34)
  %bool_37 = icmp ne i32 %v35, zeroinitializer
  br i1 %bool_37, label %if_true_entry24, label %r28
r28:
  br label %if_false_entry25
if_true_entry41:
  store i32 1, i32* %v21
  br label %next_entry43
if_false_entry42:
  store i32 0, i32* %v21
  br label %next_entry43
next_entry43:
  %v57 = call i32 @getint()
  store i32 %v57, i32* %v21
  %v63 = load i32, i32* %v21
  %bool_65 = icmp sle i32 %v63, 99
  %bool_67 = icmp ne i1 %bool_65, zeroinitializer
  br i1 %bool_67, label %l61, label %r62
l44:
  %v51 = load i32, i32* %v21
  %v52 = call i32 @func(i32 %v51)
  %bool_54 = icmp ne i32 %v52, zeroinitializer
  br i1 %bool_54, label %if_true_entry41, label %r45
r45:
  br label %if_false_entry42
if_true_entry58:
  store i32 1, i32* %v21
  br label %next_entry60
if_false_entry59:
  store i32 0, i32* %v21
  br label %next_entry60
next_entry60:
  %v74 = call i32 @getint()
  store i32 %v74, i32* %v21
  %v80 = load i32, i32* %v21
  %bool_82 = icmp sle i32 %v80, 100
  %bool_84 = icmp ne i1 %bool_82, zeroinitializer
  br i1 %bool_84, label %l78, label %r79
l61:
  br label %if_true_entry58
r62:
  %v68 = load i32, i32* %v21
  %v69 = call i32 @func(i32 %v68)
  %bool_71 = icmp ne i32 %v69, zeroinitializer
  br i1 %bool_71, label %l61, label %if_false_entry59
if_true_entry75:
  store i32 1, i32* %v21
  br label %next_entry77
if_false_entry76:
  store i32 0, i32* %v21
  br label %next_entry77
next_entry77:
  %v97 = call i32 @func(i32 99)
  %bool_99 = icmp ne i32 %v97, zeroinitializer
  %bool_101 = icmp eq i1 %bool_99, zeroinitializer
  %bool_103 = icmp ne i1 %bool_101, zeroinitializer
  br i1 %bool_103, label %l94, label %r95
l78:
  br label %if_true_entry75
r79:
  %v85 = load i32, i32* %v21
  %v86 = call i32 @func(i32 %v85)
  %bool_88 = icmp ne i32 %v86, zeroinitializer
  br i1 %bool_88, label %l78, label %if_false_entry76
if_true_entry91:
  store i32 1, i32* %v21
  br label %next_entry93
if_false_entry92:
  store i32 0, i32* %v21
  br label %next_entry93
next_entry93:
  ret i32 0
l94:
  %v105 = call i32 @func(i32 100)
  %bool_107 = icmp ne i32 %v105, zeroinitializer
  br i1 %bool_107, label %if_true_entry91, label %r95
r95:
  br label %if_false_entry92
}


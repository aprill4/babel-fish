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
main8:
  %v9 = alloca i32
  store i32 zeroinitializer, i32* %v9
  %v11 = alloca i32
  store i32 zeroinitializer, i32* %v11
  %v15 = alloca [10 x i32]
  %v18 = getelementptr [10 x i32], [10 x i32]* %v15, i32 0, i32 0
  store i32 zeroinitializer, i32* %v18
  %v20 = getelementptr [10 x i32], [10 x i32]* %v15, i32 0, i32 1
  store i32 zeroinitializer, i32* %v20
  %v22 = getelementptr [10 x i32], [10 x i32]* %v15, i32 0, i32 2
  store i32 zeroinitializer, i32* %v22
  %v24 = getelementptr [10 x i32], [10 x i32]* %v15, i32 0, i32 3
  store i32 zeroinitializer, i32* %v24
  %v26 = getelementptr [10 x i32], [10 x i32]* %v15, i32 0, i32 4
  store i32 zeroinitializer, i32* %v26
  %v28 = getelementptr [10 x i32], [10 x i32]* %v15, i32 0, i32 5
  store i32 zeroinitializer, i32* %v28
  %v30 = getelementptr [10 x i32], [10 x i32]* %v15, i32 0, i32 6
  store i32 zeroinitializer, i32* %v30
  %v32 = getelementptr [10 x i32], [10 x i32]* %v15, i32 0, i32 7
  store i32 zeroinitializer, i32* %v32
  %v34 = getelementptr [10 x i32], [10 x i32]* %v15, i32 0, i32 8
  store i32 zeroinitializer, i32* %v34
  %v36 = getelementptr [10 x i32], [10 x i32]* %v15, i32 0, i32 9
  store i32 zeroinitializer, i32* %v36
  store i32 0, i32* %v11
  store i32 0, i32* %v9
  %v41 = load i32, i32* %v9
  %bool_43 = icmp slt i32 %v41, 10
  %bool_45 = icmp ne i1 %bool_43, false
  br i1 %bool_45, label %while_entry39, label %next_entry40
while_entry39:
  %v46 = load i32, i32* %v9
  %v47 = getelementptr [10 x i32], [10 x i32]* %v15, i32 0, i32 %v46
  %v48 = load i32, i32* %v9
  %v50 = add nsw i32 %v48, 1
  store i32 %v50, i32* %v47
  %v51 = load i32, i32* %v9
  %v53 = add nsw i32 %v51, 1
  store i32 %v53, i32* %v9
  br i1 %bool_45, label %while_entry39, label %next_entry40
next_entry40:
  %v54 = alloca i32
  store i32 zeroinitializer, i32* %v54
  %v56 = alloca i32
  store i32 zeroinitializer, i32* %v56
  %v58 = alloca i32
  store i32 zeroinitializer, i32* %v58
  %v60 = alloca i32
  store i32 zeroinitializer, i32* %v60
  %v62 = alloca i32
  store i32 zeroinitializer, i32* %v62
  store i32 10, i32* %v62
  %v65 = call i32 @getint()
  store i32 %v65, i32* %v54
  %v66 = load i32, i32* %v62
  %v68 = sub nsw i32 %v66, 1
  store i32 %v68, i32* %v56
  store i32 0, i32* %v58
  %v70 = load i32, i32* %v56
  %v71 = load i32, i32* %v58
  %v72 = add nsw i32 %v70, %v71
  %v74 = sdiv i32 %v72, 2
  store i32 %v74, i32* %v60
  %v79 = load i32, i32* %v60
  %v80 = getelementptr [10 x i32], [10 x i32]* %v15, i32 0, i32 %v79
  %v81 = load i32, i32* %v80
  %v82 = load i32, i32* %v54
  %bool_83 = icmp ne i32 %v81, %v82
  %bool_85 = icmp ne i1 %bool_83, zeroinitializer
  br i1 %bool_85, label %l77, label %r78
while_entry75:
next_entry76:
  %v94 = load i32, i32* %v54
  %v95 = load i32, i32* %v60
  %v96 = getelementptr [10 x i32], [10 x i32]* %v15, i32 0, i32 %v95
  %v97 = load i32, i32* %v96
  %bool_98 = icmp eq i32 %v94, %v97
  br i1 %bool_98, label %if_true_entry91, label %if_false_entry92
l77:
  %v86 = load i32, i32* %v58
  %v87 = load i32, i32* %v56
  %bool_88 = icmp slt i32 %v86, %v87
  %bool_90 = icmp ne i1 %bool_88, zeroinitializer
  br i1 %bool_90, label %while_entry75, label %r78
r78:
  br label %next_entry76
if_true_entry91:
  %v99 = load i32, i32* %v54
  call void @putint(i32 %v99)
  br label %next_entry93
if_false_entry92:
  store i32 0, i32* %v54
  %v102 = load i32, i32* %v54
  call void @putint(i32 %v102)
  br label %next_entry93
next_entry93:
  store i32 10, i32* %v54
  %v105 = load i32, i32* %v54
  call void @putch(i32 %v105)
  ret i32 0
}


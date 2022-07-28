@a16 = global [6 x i32] [ i32 10, i32 1, i32 50, i32 50, i32 20, i32 5 ]
@dp21 = global <{ [100 x i32] }> <{ [100 x i32] zeroinitializer }>
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
main22:
  %v23 = alloca i32
  store i32 zeroinitializer, i32* %v23
  store i32 6, i32* %v23
  %v26 = alloca i32
  store i32 zeroinitializer, i32* %v26
  %v28 = alloca i32
  store i32 zeroinitializer, i32* %v28
  %v30 = alloca i32
  store i32 zeroinitializer, i32* %v30
  %v32 = alloca i32
  store i32 zeroinitializer, i32* %v32
  %v34 = alloca i32
  store i32 zeroinitializer, i32* %v34
  store i32 3, i32* %v26
  %v39 = load i32, i32* %v26
  %v40 = load i32, i32* %v23
  %bool_41 = icmp sle i32 %v39, %v40
  %bool_43 = icmp ne i1 %bool_41, false
  br i1 %bool_43, label %while_entry37, label %next_entry38
while_entry37:
  store i32 0, i32* %v28
  %v47 = load i32, i32* %v28
  %v48 = load i32, i32* %v23
  %v49 = load i32, i32* %v26
  %v50 = sub nsw i32 %v48, %v49
  %v52 = add nsw i32 %v50, 1
  %bool_53 = icmp slt i32 %v47, %v52
  %bool_55 = icmp ne i1 %bool_53, false
  br i1 %bool_55, label %while_entry45, label %next_entry46
next_entry38:
  %v129 = load i32, i32* %v23
  %v131 = sub nsw i32 %v129, 1
  %v133 = getelementptr [10 x [10 x i32]], [10 x [10 x i32]]* @dp21, i32 0, i32 0, i32 %v131
  %v134 = load i32, i32* %v133
  call void @putint(i32 %v134)
  ret i32 0
while_entry45:
  %v56 = load i32, i32* %v28
  %v57 = load i32, i32* %v26
  %v58 = add nsw i32 %v56, %v57
  %v60 = sub nsw i32 %v58, 1
  store i32 %v60, i32* %v32
  %v61 = load i32, i32* %v28
  %v63 = add nsw i32 %v61, 1
  store i32 %v63, i32* %v30
  %v66 = load i32, i32* %v30
  %v67 = load i32, i32* %v32
  %bool_68 = icmp slt i32 %v66, %v67
  %bool_70 = icmp ne i1 %bool_68, false
  br i1 %bool_70, label %while_entry64, label %next_entry65
next_entry46:
  %v125 = load i32, i32* %v26
  %v127 = add nsw i32 %v125, 1
  store i32 %v127, i32* %v26
  br i1 %bool_43, label %while_entry37, label %next_entry38
while_entry64:
  %v71 = load i32, i32* %v28
  %v72 = load i32, i32* %v30
  %v73 = getelementptr [10 x [10 x i32]], [10 x [10 x i32]]* @dp21, i32 0, i32 %v71, i32 %v72
  %v74 = load i32, i32* %v73
  %v75 = load i32, i32* %v30
  %v76 = load i32, i32* %v32
  %v77 = getelementptr [10 x [10 x i32]], [10 x [10 x i32]]* @dp21, i32 0, i32 %v75, i32 %v76
  %v78 = load i32, i32* %v77
  %v79 = add nsw i32 %v74, %v78
  %v80 = load i32, i32* %v28
  %v81 = getelementptr [6 x i32], [6 x i32]* @a16, i32 0, i32 %v80
  %v82 = load i32, i32* %v81
  %v83 = load i32, i32* %v30
  %v84 = getelementptr [6 x i32], [6 x i32]* @a16, i32 0, i32 %v83
  %v85 = load i32, i32* %v84
  %v86 = mul i32 %v82, %v85
  %v87 = load i32, i32* %v32
  %v88 = getelementptr [6 x i32], [6 x i32]* @a16, i32 0, i32 %v87
  %v89 = load i32, i32* %v88
  %v90 = mul i32 %v86, %v89
  %v91 = add nsw i32 %v79, %v90
  store i32 %v91, i32* %v34
  %v97 = load i32, i32* %v28
  %v98 = load i32, i32* %v32
  %v99 = getelementptr [10 x [10 x i32]], [10 x [10 x i32]]* @dp21, i32 0, i32 %v97, i32 %v98
  %v100 = load i32, i32* %v99
  %bool_102 = icmp ne i32 %v100, zeroinitializer
  %bool_104 = icmp eq i1 %bool_102, zeroinitializer
  %bool_106 = icmp ne i1 %bool_104, zeroinitializer
  br i1 %bool_106, label %l95, label %r96
next_entry65:
  %v122 = load i32, i32* %v28
  %v124 = add nsw i32 %v122, 1
  store i32 %v124, i32* %v28
  br i1 %bool_55, label %while_entry45, label %next_entry46
if_true_entry92:
  %v115 = load i32, i32* %v28
  %v116 = load i32, i32* %v32
  %v117 = getelementptr [10 x [10 x i32]], [10 x [10 x i32]]* @dp21, i32 0, i32 %v115, i32 %v116
  %v118 = load i32, i32* %v34
  store i32 %v118, i32* %v117
  br label %next_entry94
next_entry94:
  %v119 = load i32, i32* %v30
  %v121 = add nsw i32 %v119, 1
  store i32 %v121, i32* %v30
  br i1 %bool_70, label %while_entry64, label %next_entry65
l95:
  br label %while_entry64
r96:
  %v107 = load i32, i32* %v34
  %v108 = load i32, i32* %v28
  %v109 = load i32, i32* %v32
  %v110 = getelementptr [10 x [10 x i32]], [10 x [10 x i32]]* @dp21, i32 0, i32 %v108, i32 %v109
  %v111 = load i32, i32* %v110
  %bool_112 = icmp slt i32 %v107, %v111
  %bool_114 = icmp ne i1 %bool_112, zeroinitializer
  br i1 %bool_114, label %l95, label %next_entry94
}


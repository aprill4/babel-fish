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
define i32 @lengthOfLastWord(i32* , i32 ) {
lengthOfLastWord10:
  %v11 = alloca i32
  %v12 = alloca i32
  %v16 = load i32, i32* %v12
  %bool_18 = icmp eq i32 %v16, 0
  br i1 %bool_18, label %if_true_entry13, label %next_entry15
if_true_entry13:
  ret i32 0
next_entry15:
  %v20 = alloca i32
  store i32 zeroinitializer, i32* %v20
  %v22 = load i32, i32* %v12
  %v24 = sub nsw i32 %v22, 1
  store i32 %v24, i32* %v20
  %v29 = load i32, i32* %v20
  %v32 = sub nsw i32 0, 1
  %bool_33 = icmp sgt i32 %v29, %v32
  %bool_35 = icmp ne i1 %bool_33, zeroinitializer
  br i1 %bool_35, label %l27, label %r28
while_entry25:
next_entry26:
  %v46 = load i32, i32* %v20
  %v49 = sub nsw i32 0, 1
  %bool_50 = icmp eq i32 %v46, %v49
  br i1 %bool_50, label %if_true_entry43, label %next_entry45
l27:
  %v36 = load i32, i32* %v20
  %v37 = getelementptr i32, i32* %v11, i32 0, i32 %v36
  %v38 = load i32, i32* %v37
  %bool_40 = icmp eq i32 %v38, 0
  %bool_42 = icmp ne i1 %bool_40, zeroinitializer
  br i1 %bool_42, label %while_entry25, label %r28
r28:
  br label %next_entry26
if_true_entry43:
  ret i32 0
next_entry45:
  %v52 = alloca i32
  store i32 zeroinitializer, i32* %v52
  %v54 = load i32, i32* %v20
  store i32 %v54, i32* %v52
  %v57 = load i32, i32* %v52
  %v60 = sub nsw i32 0, 1
  %bool_61 = icmp sgt i32 %v57, %v60
  %bool_63 = icmp ne i1 %bool_61, false
  br i1 %bool_63, label %while_entry55, label %next_entry56
while_entry55:
  %v67 = load i32, i32* %v52
  %v68 = getelementptr i32, i32* %v11, i32 0, i32 %v67
  %v69 = load i32, i32* %v68
  %bool_71 = icmp eq i32 %v69, 0
  br i1 %bool_71, label %if_true_entry64, label %next_entry66
next_entry56:
  %v86 = load i32, i32* %v20
  %v87 = load i32, i32* %v52
  %v88 = sub nsw i32 %v86, %v87
  ret i32 %v88
if_true_entry64:
  %v72 = load i32, i32* %v12
  %v73 = load i32, i32* %v52
  %v74 = sub nsw i32 %v72, %v73
  %v76 = sub nsw i32 %v74, 1
  %v77 = load i32, i32* %v12
  %v79 = sub nsw i32 %v77, 1
  %v80 = load i32, i32* %v20
  %v81 = sub nsw i32 %v79, %v80
  %v82 = sub nsw i32 %v76, %v81
  ret i32 %v82
next_entry66:
  %v83 = load i32, i32* %v52
  %v85 = sub nsw i32 %v83, 1
  store i32 %v85, i32* %v52
  br i1 %bool_63, label %while_entry55, label %next_entry56
}
define i32 @main() {
main89:
  %v90 = alloca i32
  store i32 zeroinitializer, i32* %v90
  %v94 = alloca [10 x i32]
  %v97 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 0
  store i32 zeroinitializer, i32* %v97
  %v99 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 1
  store i32 zeroinitializer, i32* %v99
  %v101 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 2
  store i32 zeroinitializer, i32* %v101
  %v103 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 3
  store i32 zeroinitializer, i32* %v103
  %v105 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 4
  store i32 zeroinitializer, i32* %v105
  %v107 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 5
  store i32 zeroinitializer, i32* %v107
  %v109 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 6
  store i32 zeroinitializer, i32* %v109
  %v111 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 7
  store i32 zeroinitializer, i32* %v111
  %v113 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 8
  store i32 zeroinitializer, i32* %v113
  %v115 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 9
  store i32 zeroinitializer, i32* %v115
  %v118 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 0
  %v121 = sub nsw i32 0, 4
  store i32 %v121, i32* %v118
  %v124 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 1
  store i32 3, i32* %v124
  %v128 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 2
  store i32 9, i32* %v128
  %v132 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 3
  %v135 = sub nsw i32 0, 2
  store i32 %v135, i32* %v132
  %v138 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 4
  store i32 0, i32* %v138
  %v142 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 5
  store i32 1, i32* %v142
  %v146 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 6
  %v149 = sub nsw i32 0, 6
  store i32 %v149, i32* %v146
  %v152 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 7
  store i32 5, i32* %v152
  %v156 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 8
  store i32 7, i32* %v156
  %v160 = getelementptr [10 x i32], [10 x i32]* %v94, i32 0, i32 9
  store i32 8, i32* %v160
  store i32 10, i32* %v90
  %v163 = load [10 x i32], [10 x i32]* %v94
  %v164 = load i32, i32* %v90
  %v165 = call i32 @lengthOfLastWord([10 x i32] %v163, i32 %v164)
  store i32 %v165, i32* %v90
  %v166 = load i32, i32* %v90
  ret i32 %v166
}


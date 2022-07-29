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
define i32 @uniquePaths(i32 , i32 ) {
uniquePaths10:
  %v11 = alloca i32
  %v12 = alloca i32
  %v18 = load i32, i32* %v11
  %bool_20 = icmp eq i32 %v18, 1
  %bool_22 = icmp ne i1 %bool_20, zeroinitializer
  br i1 %bool_22, label %l16, label %r17
if_true_entry13:
  ret i32 1
next_entry15:
  %v31 = alloca [9 x i32]
  %v34 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 0
  store i32 zeroinitializer, i32* %v34
  %v36 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 1
  store i32 zeroinitializer, i32* %v36
  %v38 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 2
  store i32 zeroinitializer, i32* %v38
  %v40 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 3
  store i32 zeroinitializer, i32* %v40
  %v42 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 4
  store i32 zeroinitializer, i32* %v42
  %v44 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 5
  store i32 zeroinitializer, i32* %v44
  %v46 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 6
  store i32 zeroinitializer, i32* %v46
  %v48 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 7
  store i32 zeroinitializer, i32* %v48
  %v50 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 8
  store i32 zeroinitializer, i32* %v50
  %v51 = alloca i32
  store i32 zeroinitializer, i32* %v51
  %v53 = alloca i32
  store i32 zeroinitializer, i32* %v53
  store i32 0, i32* %v51
  %v58 = load i32, i32* %v51
  %v59 = load i32, i32* %v11
  %bool_60 = icmp slt i32 %v58, %v59
  %bool_62 = icmp ne i1 %bool_60, false
  br i1 %bool_62, label %while_entry56, label %next_entry57
l16:
  br label %if_true_entry13
r17:
  %v23 = load i32, i32* %v12
  %bool_25 = icmp eq i32 %v23, 1
  %bool_27 = icmp ne i1 %bool_25, zeroinitializer
  br i1 %bool_27, label %l16, label %next_entry15
while_entry56:
  %v63 = load i32, i32* %v51
  %v65 = mul i32 %v63, 3
  %v66 = load i32, i32* %v12
  %v67 = add nsw i32 %v65, %v66
  %v69 = sub nsw i32 %v67, 1
  %v70 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 %v69
  store i32 1, i32* %v70
  %v72 = load i32, i32* %v51
  %v74 = add nsw i32 %v72, 1
  store i32 %v74, i32* %v51
  br i1 %bool_62, label %while_entry56, label %next_entry57
next_entry57:
  store i32 0, i32* %v51
  %v78 = load i32, i32* %v51
  %v79 = load i32, i32* %v12
  %bool_80 = icmp slt i32 %v78, %v79
  %bool_82 = icmp ne i1 %bool_80, false
  br i1 %bool_82, label %while_entry76, label %next_entry77
while_entry76:
  %v83 = load i32, i32* %v11
  %v85 = sub nsw i32 %v83, 1
  %v87 = mul i32 %v85, 3
  %v88 = load i32, i32* %v51
  %v89 = add nsw i32 %v87, %v88
  %v90 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 %v89
  store i32 1, i32* %v90
  %v92 = load i32, i32* %v51
  %v94 = add nsw i32 %v92, 1
  store i32 %v94, i32* %v51
  br i1 %bool_82, label %while_entry76, label %next_entry77
next_entry77:
  %v95 = load i32, i32* %v11
  %v97 = sub nsw i32 %v95, 2
  store i32 %v97, i32* %v51
  %v100 = load i32, i32* %v51
  %v103 = sub nsw i32 0, 1
  %bool_104 = icmp sgt i32 %v100, %v103
  %bool_106 = icmp ne i1 %bool_104, false
  br i1 %bool_106, label %while_entry98, label %next_entry99
while_entry98:
  %v107 = load i32, i32* %v12
  %v109 = sub nsw i32 %v107, 2
  store i32 %v109, i32* %v53
  %v112 = load i32, i32* %v53
  %v115 = sub nsw i32 0, 1
  %bool_116 = icmp sgt i32 %v112, %v115
  %bool_118 = icmp ne i1 %bool_116, false
  br i1 %bool_118, label %while_entry110, label %next_entry111
next_entry99:
  %v152 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 0
  %v153 = load i32, i32* %v152
  ret i32 %v153
while_entry110:
  %v119 = load i32, i32* %v51
  %v121 = mul i32 %v119, 3
  %v122 = load i32, i32* %v53
  %v123 = add nsw i32 %v121, %v122
  %v124 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 %v123
  %v125 = load i32, i32* %v51
  %v127 = add nsw i32 %v125, 1
  %v129 = mul i32 %v127, 3
  %v130 = load i32, i32* %v53
  %v131 = add nsw i32 %v129, %v130
  %v132 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 %v131
  %v133 = load i32, i32* %v132
  %v134 = load i32, i32* %v51
  %v136 = mul i32 %v134, 3
  %v137 = load i32, i32* %v53
  %v138 = add nsw i32 %v136, %v137
  %v140 = add nsw i32 %v138, 1
  %v141 = getelementptr [9 x i32], [9 x i32]* %v31, i32 0, i32 %v140
  %v142 = load i32, i32* %v141
  %v143 = add nsw i32 %v133, %v142
  store i32 %v143, i32* %v124
  %v144 = load i32, i32* %v53
  %v146 = sub nsw i32 %v144, 1
  store i32 %v146, i32* %v53
  br i1 %bool_118, label %while_entry110, label %next_entry111
next_entry111:
  %v147 = load i32, i32* %v51
  %v149 = sub nsw i32 %v147, 1
  store i32 %v149, i32* %v51
  br i1 %bool_106, label %while_entry98, label %next_entry99
}
define i32 @main() {
main154:
  %v155 = alloca i32
  store i32 zeroinitializer, i32* %v155
  %v157 = alloca i32
  store i32 zeroinitializer, i32* %v157
  store i32 3, i32* %v157
  %v160 = load i32, i32* %v157
  %v161 = load i32, i32* %v157
  %v162 = call i32 @uniquePaths(i32 %v160, i32 %v161)
  store i32 %v162, i32* %v155
  %v163 = load i32, i32* %v155
  ret i32 %v163
}


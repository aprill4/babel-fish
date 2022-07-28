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
  %v36 = alloca [5 x [5 x i32]]
  %v41 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 0, i32 0
  store i32 1, i32* %v41
  %v44 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 0, i32 1
  store i32 1, i32* %v44
  %v47 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 0, i32 2
  store i32 1, i32* %v47
  %v50 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 0, i32 3
  store i32 1, i32* %v50
  %v53 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 0, i32 4
  store i32 1, i32* %v53
  %v56 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 1, i32 0
  store i32 2, i32* %v56
  %v59 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 1, i32 1
  store i32 2, i32* %v59
  %v62 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 1, i32 2
  store i32 2, i32* %v62
  %v65 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 1, i32 3
  store i32 2, i32* %v65
  %v68 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 1, i32 4
  store i32 2, i32* %v68
  %v71 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 2, i32 0
  store i32 3, i32* %v71
  %v74 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 2, i32 1
  store i32 3, i32* %v74
  %v77 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 2, i32 2
  store i32 3, i32* %v77
  %v80 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 2, i32 3
  store i32 3, i32* %v80
  %v83 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 2, i32 4
  store i32 3, i32* %v83
  %v86 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 3, i32 0
  store i32 4, i32* %v86
  %v89 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 3, i32 1
  store i32 4, i32* %v89
  %v92 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 3, i32 2
  store i32 4, i32* %v92
  %v95 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 3, i32 3
  store i32 4, i32* %v95
  %v98 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 3, i32 4
  store i32 4, i32* %v98
  %v101 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 4, i32 0
  store i32 5, i32* %v101
  %v104 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 4, i32 1
  store i32 5, i32* %v104
  %v107 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 4, i32 2
  store i32 5, i32* %v107
  %v110 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 4, i32 3
  store i32 5, i32* %v110
  %v113 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 4, i32 4
  store i32 5, i32* %v113
  %v114 = alloca i32
  store i32 zeroinitializer, i32* %v114
  %v116 = alloca i32
  store i32 zeroinitializer, i32* %v116
  %v118 = alloca i32
  store i32 zeroinitializer, i32* %v118
  %v120 = alloca i32
  store i32 zeroinitializer, i32* %v120
  store i32 2, i32* %v114
  store i32 3, i32* %v116
  store i32 0, i32* %v120
  %v127 = load i32, i32* %v120
  %bool_129 = icmp slt i32 %v127, 5
  %bool_131 = icmp ne i1 %bool_129, false
  br i1 %bool_131, label %while_entry125, label %next_entry126
while_entry125:
  %v132 = load i32, i32* %v114
  %v134 = sub nsw i32 %v132, 1
  %v135 = load i32, i32* %v120
  %v136 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 %v134, i32 %v135
  %v137 = load i32, i32* %v136
  store i32 %v137, i32* %v118
  %v138 = load i32, i32* %v114
  %v140 = sub nsw i32 %v138, 1
  %v141 = load i32, i32* %v120
  %v142 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 %v140, i32 %v141
  %v143 = load i32, i32* %v116
  %v145 = sub nsw i32 %v143, 1
  %v146 = load i32, i32* %v120
  %v147 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 %v145, i32 %v146
  %v148 = load i32, i32* %v147
  store i32 %v148, i32* %v142
  %v149 = load i32, i32* %v116
  %v151 = sub nsw i32 %v149, 1
  %v152 = load i32, i32* %v120
  %v153 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 %v151, i32 %v152
  %v154 = load i32, i32* %v118
  store i32 %v154, i32* %v153
  %v155 = load i32, i32* %v120
  %v157 = add nsw i32 %v155, 1
  store i32 %v157, i32* %v120
  br i1 %bool_131, label %while_entry125, label %next_entry126
next_entry126:
  %v162 = getelementptr [5 x [5 x i32]], [5 x [5 x i32]]* %v36, i32 0, i32 2, i32 0
  %v163 = load i32, i32* %v162
  ret i32 %v163
}


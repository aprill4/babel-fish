@g9 = global i32 zeroinitializer
@h11 = global i32 zeroinitializer
@f13 = global i32 zeroinitializer
@e15 = global i32 zeroinitializer
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
define i32 @EightWhile() {
EightWhile16:
  %v17 = alloca i32
  store i32 zeroinitializer, i32* %v17
  store i32 5, i32* %v17
  %v20 = alloca i32
  store i32 zeroinitializer, i32* %v20
  %v22 = alloca i32
  store i32 zeroinitializer, i32* %v22
  store i32 6, i32* %v20
  store i32 7, i32* %v22
  %v26 = alloca i32
  store i32 zeroinitializer, i32* %v26
  store i32 10, i32* %v26
  %v31 = load i32, i32* %v17
  %bool_33 = icmp slt i32 %v31, 20
  %bool_35 = icmp ne i1 %bool_33, false
  br i1 %bool_35, label %while_entry29, label %next_entry30
while_entry29:
  %v36 = load i32, i32* %v17
  %v38 = add nsw i32 %v36, 3
  store i32 %v38, i32* %v17
  %v41 = load i32, i32* %v20
  %bool_43 = icmp slt i32 %v41, 10
  %bool_45 = icmp ne i1 %bool_43, false
  br i1 %bool_45, label %while_entry39, label %next_entry40
next_entry30:
  %v130 = load i32, i32* %v17
  %v131 = load i32, i32* %v20
  %v132 = load i32, i32* %v26
  %v133 = add nsw i32 %v131, %v132
  %v134 = add nsw i32 %v130, %v133
  %v135 = load i32, i32* %v22
  %v136 = add nsw i32 %v134, %v135
  %v137 = load i32, i32* @e15
  %v138 = load i32, i32* %v26
  %v139 = add nsw i32 %v137, %v138
  %v140 = load i32, i32* @g9
  %v141 = sub nsw i32 %v139, %v140
  %v142 = load i32, i32* @h11
  %v143 = add nsw i32 %v141, %v142
  %v144 = sub nsw i32 %v136, %v143
  ret i32 %v144
while_entry39:
  %v46 = load i32, i32* %v20
  %v48 = add nsw i32 %v46, 1
  store i32 %v48, i32* %v20
  %v51 = load i32, i32* %v22
  %bool_53 = icmp eq i32 %v51, 7
  %bool_55 = icmp ne i1 %bool_53, false
  br i1 %bool_55, label %while_entry49, label %next_entry50
next_entry40:
  %v127 = load i32, i32* %v20
  %v129 = sub nsw i32 %v127, 2
  store i32 %v129, i32* %v20
  br i1 %bool_35, label %while_entry29, label %next_entry30
while_entry49:
  %v56 = load i32, i32* %v22
  %v58 = sub nsw i32 %v56, 1
  store i32 %v58, i32* %v22
  %v61 = load i32, i32* %v26
  %bool_63 = icmp slt i32 %v61, 20
  %bool_65 = icmp ne i1 %bool_63, false
  br i1 %bool_65, label %while_entry59, label %next_entry60
next_entry50:
  %v124 = load i32, i32* %v22
  %v126 = add nsw i32 %v124, 1
  store i32 %v126, i32* %v22
  br i1 %bool_45, label %while_entry39, label %next_entry40
while_entry59:
  %v66 = load i32, i32* %v26
  %v68 = add nsw i32 %v66, 3
  store i32 %v68, i32* %v26
  %v71 = load i32, i32* @e15
  %bool_73 = icmp sgt i32 %v71, 1
  %bool_75 = icmp ne i1 %bool_73, false
  br i1 %bool_75, label %while_entry69, label %next_entry70
next_entry60:
  %v121 = load i32, i32* %v26
  %v123 = sub nsw i32 %v121, 1
  store i32 %v123, i32* %v26
  br i1 %bool_55, label %while_entry49, label %next_entry50
while_entry69:
  %v76 = load i32, i32* @e15
  %v78 = sub nsw i32 %v76, 1
  store i32 %v78, i32* @e15
  %v81 = load i32, i32* @f13
  %bool_83 = icmp sgt i32 %v81, 2
  %bool_85 = icmp ne i1 %bool_83, false
  br i1 %bool_85, label %while_entry79, label %next_entry80
next_entry70:
  %v118 = load i32, i32* @e15
  %v120 = add nsw i32 %v118, 1
  store i32 %v120, i32* @e15
  br i1 %bool_65, label %while_entry59, label %next_entry60
while_entry79:
  %v86 = load i32, i32* @f13
  %v88 = sub nsw i32 %v86, 2
  store i32 %v88, i32* @f13
  %v91 = load i32, i32* @g9
  %bool_93 = icmp slt i32 %v91, 3
  %bool_95 = icmp ne i1 %bool_93, false
  br i1 %bool_95, label %while_entry89, label %next_entry90
next_entry80:
  %v115 = load i32, i32* @f13
  %v117 = add nsw i32 %v115, 1
  store i32 %v117, i32* @f13
  br i1 %bool_75, label %while_entry69, label %next_entry70
while_entry89:
  %v96 = load i32, i32* @g9
  %v98 = add nsw i32 %v96, 10
  store i32 %v98, i32* @g9
  %v101 = load i32, i32* @h11
  %bool_103 = icmp slt i32 %v101, 10
  %bool_105 = icmp ne i1 %bool_103, false
  br i1 %bool_105, label %while_entry99, label %next_entry100
next_entry90:
  %v112 = load i32, i32* @g9
  %v114 = sub nsw i32 %v112, 8
  store i32 %v114, i32* @g9
  br i1 %bool_85, label %while_entry79, label %next_entry80
while_entry99:
  %v106 = load i32, i32* @h11
  %v108 = add nsw i32 %v106, 8
  store i32 %v108, i32* @h11
  br i1 %bool_105, label %while_entry99, label %next_entry100
next_entry100:
  %v109 = load i32, i32* @h11
  %v111 = sub nsw i32 %v109, 1
  store i32 %v111, i32* @h11
  br i1 %bool_95, label %while_entry89, label %next_entry90
}
define i32 @main() {
main145:
  store i32 1, i32* @g9
  store i32 2, i32* @h11
  store i32 4, i32* @e15
  store i32 6, i32* @f13
  %v150 = call i32 @EightWhile()
  ret i32 %v150
}


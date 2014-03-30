select Course_name from course where course_number = (select course_number from section where Instructor = 'king' and (year = '07' or year = '08'))

select course_number, semester, year, count(student_number) from grade_report where course_number IN (select course_number from section where Instructor = 'king' and (year = '07' or year = '08')) 
and section_identifier in (select course_number from section where Instructor = 'king' and (year = '07' or year = '08'))


select Name, Course_name, Se.Course_number, Credit_hours, Semester, year, Grade 
From STUDENT as S, COURSE as C, SECTION as Se, GRADE_REPORT as G 
where S.Class = 2 and S.Major = 'CS' and G.Student_number = S.Student_number 
and G.Section_identifier = Se.Section_identifier
and Se.Course_number = C.Course_number;

select Name, Course_name, C.Course_number, Credit_hours, Semester, year, Grade 
From STUDENT as S, COURSE as C, SECTION as Se, GRADE_REPORT as G 
where C.Course_number in (select Se.course_number from section 
	where section_identifier in (select g.section_identifier from grade_report 
		where g.student_number in (select s.Student_number from student where S.Class = 2 and S.Major = 'CS')))
select Course_number, Semester, Year, count(Student_number) from SECTION as S, GRADE_REPORT as G where Instructor = 'King' AND (Year = '07' OR Year = '08') AND S.Section_identifier = G.Section_identifier;


select Name, Course_name, Se.Course_number, Credit_hours, Semester, year, Grade 
From STUDENT as S, COURSE as C, SECTION as Se, GRADE_REPORT as G 
where S.Class = 2 and S.Major = 'CS' and G.Student_number = S.Student_number 
and G.Section_identifier = Se.Section_identifier
and Se.Course_number = C.Course_number;

insert into STUDENT values ('Johnson', 25, 1,'Math');

update STUDENT
set Class = Class * 2
where Student_number = 17;

insert into COURSE values ('Knowledge Engineering', 'CS4390', 3, 'CS')

delete from STUDENT
where Name = 'Smith' and Student_number = 17


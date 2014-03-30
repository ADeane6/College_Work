
-- -----------------------------------------------------
-- change project to whatever your database is called
-- -----------------------------------------------------
USE `project`;

DROP TABLE IF EXISTS `PREREQUISITE`;
DROP TABLE IF EXISTS `GRADE_REPORT`;
DROP TABLE IF EXISTS `SECTION`;
DROP TABLE IF EXISTS `COURSE`;
DROP TABLE IF EXISTS `STUDENT`;

-- -----------------------------------------------------
-- Table `STUDENT`
-- -----------------------------------------------------

CREATE TABLE IF NOT EXISTS `STUDENT` (
  `Name` VARCHAR(15) NOT NULL,
  `Student_number` INT NOT NULL,
  `Class` INT NOT NULL,
  `Major` VARCHAR(4) NOT NULL,
  UNIQUE INDEX `Student_number_UNIQUE` (`Student_number` ASC),
  PRIMARY KEY (`Student_number`))
ENGINE = InnoDB;
INSERT INTO `STUDENT` VALUES ('Brown',8,2,'CS'),('Smith',17,1,'CS');

-- -----------------------------------------------------
-- Table `COURSE`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `COURSE` (
  `Course_name` VARCHAR(45) NOT NULL,
  `Course_number` VARCHAR(45) NOT NULL,
  `Credit_hours` INT NOT NULL,
  `Department` VARCHAR(4) NOT NULL,
  PRIMARY KEY (`Course_number`))
ENGINE = InnoDB;
INSERT INTO `COURSE` VALUES ('Intro to Computer Science','CS1310',4,'CS'),('Data Structures','CS3320',4,'CS'),('Database','CS3380',3,'CS'),('Discrete Mathematics','MATH2410',3,'MATH');


-- -----------------------------------------------------
-- Table `SECTION`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `SECTION` (
  `Course_number` VARCHAR(45) NOT NULL,
  `Semester` VARCHAR(45) NOT NULL,
  `Year` VARCHAR(2) NOT NULL,
  `Instructor` VARCHAR(45) NOT NULL,
  `Section_identifier` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Section_identifier`),
  INDEX `fk_SECTION_COURSE1_idx` (`Course_number` ASC),
  CONSTRAINT `fk_SECTION_COURSE1`
    FOREIGN KEY (`Course_number`)
    REFERENCES `COURSE` (`Course_number`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;
INSERT INTO `SECTION` VALUES ('CS3320','Spring','08','Knuth','102'),('MATH2410','Fall','08','Chang','112'),('CS1310','Fall','08','Anderson','119'),('CS3380','Fall','08','Stone','135'),('MATH2410','Fall','07','King','85'),('CS1310','Fall','07','Anderson','92');

-- -----------------------------------------------------
-- Table `GRADE_REPORT`
-- -----------------------------------------------------

CREATE TABLE IF NOT EXISTS `GRADE_REPORT` (
  `Student_number` INT NOT NULL,
  `Section_identifier` VARCHAR(45) NOT NULL,
  `Grade` VARCHAR(2) NOT NULL,
  `Grade_id` INT NULL AUTO_INCREMENT,
  INDEX `fk_GRADE_REPORT_STUDENT1_idx` (`Student_number` ASC),
  INDEX `fk_GRADE_REPORT_SECTION1_idx` (`Section_identifier` ASC),
  PRIMARY KEY (`Grade_id`),
  CONSTRAINT `fk_GRADE_REPORT_STUDENT1`
    FOREIGN KEY (`Student_number`)
    REFERENCES `STUDENT` (`Student_number`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_GRADE_REPORT_SECTION1`
    FOREIGN KEY (`Section_identifier`)
    REFERENCES `SECTION` (`Section_identifier`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;
INSERT INTO `GRADE_REPORT` VALUES (17,112,'B',1),(17,119,'C',2),(8,85,'A',3),(8,92,'A',4),(8,102,'B',5),(8,135,'A',6);

-- -----------------------------------------------------
-- Table `PREREQUISITE`
-- -----------------------------------------------------

CREATE TABLE IF NOT EXISTS `PREREQUISITE` (
  `Course_number` VARCHAR(8) NOT NULL,
  `Prerequisite_number` VARCHAR(8) NOT NULL,
  `Prereq_id` INT NULL AUTO_INCREMENT,
  INDEX `fk_PREREQUISITE_COURSE1_idx` (`Course_number` ASC),
  INDEX `fk_PREREQUISITE_COURSE2_idx` (`Prerequisite_number` ASC),
  PRIMARY KEY (`Prereq_id`),
  CONSTRAINT `fk_PREREQUISITE_COURSE1`
    FOREIGN KEY (`Course_number`)
    REFERENCES `COURSE` (`Course_number`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_PREREQUISITE_COURSE2`
    FOREIGN KEY (`Prerequisite_number`)
    REFERENCES `COURSE` (`Course_number`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;
INSERT INTO `PREREQUISITE` VALUES ('CS3380','CS3320',1),('CS3380','MATH2410',2),('CS3320','CS1310',3);


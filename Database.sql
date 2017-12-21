-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.1.50-community


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema students
--

CREATE DATABASE IF NOT EXISTS students;
USE students;

--
-- Definition of table `score`
--

DROP TABLE IF EXISTS `score`;
CREATE TABLE `score` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(20) DEFAULT NULL,
  `Chinese` int(10) DEFAULT '0',
  `Math` int(10) DEFAULT '0',
  `English` int(10) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=25 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `score`
--

/*!40000 ALTER TABLE `score` DISABLE KEYS */;
INSERT INTO `score` (`id`,`name`,`Chinese`,`Math`,`English`) VALUES 
 (1,'张三',80,79,90),
 (2,'李四',90,98,70),
 (3,'王五',60,80,95),
 (4,'赵六',80,70,80),
 (5,'Gorden',78,70,100),
 (6,'Sammy',78,80,89),
 (7,'Jim',88,79,99),
 (8,'Jay',100,56,79),
 (10,'Hikari',90,80,70),
 (15,'eee',45,68,54),
 (16,'yuri',80,87,70),
 (17,'ggg',89,90,90),
 (19,'土霸',78,90,56),
 (20,'而立',78,88,78),
 (21,'fffr',78,90,70),
 (22,'张布凡',86,95,97),
 (23,'刘扬',79,80,90);
/*!40000 ALTER TABLE `score` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;

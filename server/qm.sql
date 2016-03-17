PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE workType
(
workTypeNo integer primary key,/*工种号*/
productName text not null/*产品名称*/
);
INSERT INTO "workType" VALUES(0,'unknown');
INSERT INTO "workType" VALUES(1,'纽扣');
INSERT INTO "workType" VALUES(2,'拉链');
INSERT INTO "workType" VALUES(3,'belt');
INSERT INTO "workType" VALUES(4,'衬料');
INSERT INTO "workType" VALUES(5,'hat');
INSERT INTO "workType" VALUES(6,'领带');
INSERT INTO "workType" VALUES(7,'tie');
INSERT INTO "workType" VALUES(8,'手套');
INSERT INTO "workType" VALUES(9,'袜子');
INSERT INTO "workType" VALUES(10,'T-shirt');
INSERT INTO "workType" VALUES(11,'衬衣');
INSERT INTO "workType" VALUES(12,'coat');
INSERT INTO "workType" VALUES(13,'suits');
INSERT INTO "workType" VALUES(14,'jacket');
INSERT INTO "workType" VALUES(15,'pants');
CREATE TABLE quality
(
qualityNo integer primary key,/*品质号*/
drawback text not null,/*具体缺陷名称*/
workTypeNo integer not null/*工种号*/
);
INSERT INTO "quality" VALUES(1,'A合格',1);
INSERT INTO "quality" VALUES(2,'B次品色差',1);
INSERT INTO "quality" VALUES(3,'B次品厚度',1);
INSERT INTO "quality" VALUES(4,'B次品长度',1);
INSERT INTO "quality" VALUES(5,'B次品光度',1);
INSERT INTO "quality" VALUES(6,'B次品型号',1);
INSERT INTO "quality" VALUES(7,'C可维修色差',1);
INSERT INTO "quality" VALUES(8,'C可维修厚度',1);
INSERT INTO "quality" VALUES(9,'C可维修长度',1);
INSERT INTO "quality" VALUES(10,'C可维修光度',1);
INSERT INTO "quality" VALUES(11,'C可维修型号',1);
INSERT INTO "quality" VALUES(12,'D需销毁',1);
INSERT INTO "quality" VALUES(13,'A合格',2);
INSERT INTO "quality" VALUES(14,'B次品色差',2);
INSERT INTO "quality" VALUES(15,'B次品布带厚度',2);
INSERT INTO "quality" VALUES(16,'B次品牙链弧度',2);
INSERT INTO "quality" VALUES(17,'B次品带筋大小',2);
INSERT INTO "quality" VALUES(18,'B次品带筋位置',2);
INSERT INTO "quality" VALUES(19,'C可维修色差',2);
INSERT INTO "quality" VALUES(20,'C可维修布带厚度',2);
INSERT INTO "quality" VALUES(21,'C可维修牙链弧度',2);
INSERT INTO "quality" VALUES(22,'C可维修带筋大小',2);
INSERT INTO "quality" VALUES(23,'C可维修带筋位置',2);
INSERT INTO "quality" VALUES(24,'D需销毁',2);
INSERT INTO "quality" VALUES(25,'A合格',3);
INSERT INTO "quality" VALUES(26,'B次品皮革厚度',3);
INSERT INTO "quality" VALUES(27,'B次品带扣厚度',3);
INSERT INTO "quality" VALUES(28,'B次品带孔光滑度',3);
INSERT INTO "quality" VALUES(29,'B次品带孔大小',3);
INSERT INTO "quality" VALUES(30,'B次品带圈光滑度',3);
INSERT INTO "quality" VALUES(31,'C可维修皮革厚度',3);
INSERT INTO "quality" VALUES(32,'C可维修带扣厚度',3);
INSERT INTO "quality" VALUES(33,'C可维修带孔光滑度',3);
INSERT INTO "quality" VALUES(34,'C可维修带孔大小',3);
INSERT INTO "quality" VALUES(35,'C可维修带圈光滑度',3);
INSERT INTO "quality" VALUES(36,'D需销毁',3);
INSERT INTO "quality" VALUES(37,'A合格',8);
INSERT INTO "quality" VALUES(38,'B次品尺寸',8);
INSERT INTO "quality" VALUES(39,'B次品色差',8);
INSERT INTO "quality" VALUES(40,'B次品手感',8);
INSERT INTO "quality" VALUES(41,'B次品密度',8);
INSERT INTO "quality" VALUES(42,'B次品污渍',8);
INSERT INTO "quality" VALUES(43,'C可维修尺寸',8);
INSERT INTO "quality" VALUES(44,'C可维修色差',8);
INSERT INTO "quality" VALUES(45,'C可维修手感',8);
INSERT INTO "quality" VALUES(46,'C可维修密度',8);
INSERT INTO "quality" VALUES(47,'C可维修污渍',8);
INSERT INTO "quality" VALUES(48,'D需销毁',8);
INSERT INTO "quality" VALUES(51,'A-Range',1);
INSERT INTO "quality" VALUES(52,'B-Range',1);
INSERT INTO "quality" VALUES(53,'C-Range',1);
INSERT INTO "quality" VALUES(54,'A-Great',1);
INSERT INTO "quality" VALUES(55,'B-OK',1);
INSERT INTO "quality" VALUES(56,'C-Repair',1);
INSERT INTO "quality" VALUES(57,'D-Bad',1);
INSERT INTO "quality" VALUES(58,'D-Range',1);
INSERT INTO "quality" VALUES(61,'A-color',2);
INSERT INTO "quality" VALUES(62,'B-style',2);
INSERT INTO "quality" VALUES(63,'C-feeling',2);
INSERT INTO "quality" VALUES(64,'A-Great',2);
INSERT INTO "quality" VALUES(65,'B-OK',2);
INSERT INTO "quality" VALUES(66,'C-Repair',2);
INSERT INTO "quality" VALUES(67,'D-Bad',2);
INSERT INTO "quality" VALUES(68,'D-price',2);
INSERT INTO "quality" VALUES(71,'A-color',13);
INSERT INTO "quality" VALUES(72,'B-style',13);
INSERT INTO "quality" VALUES(73,'C-feeling',13);
INSERT INTO "quality" VALUES(74,'A-Great',13);
INSERT INTO "quality" VALUES(75,'B-OK',12);
INSERT INTO "quality" VALUES(76,'C-Repair',13);
INSERT INTO "quality" VALUES(77,'D-Bad',13);
INSERT INTO "quality" VALUES(78,'D-price',13);
INSERT INTO "quality" VALUES(81,'A-color',14);
INSERT INTO "quality" VALUES(82,'B-style',14);
INSERT INTO "quality" VALUES(83,'C-feeling',14);
INSERT INTO "quality" VALUES(84,'A-Great',14);
INSERT INTO "quality" VALUES(85,'B-OK',14);
INSERT INTO "quality" VALUES(86,'C-Repair',14);
INSERT INTO "quality" VALUES(87,'D-Bad',14);
INSERT INTO "quality" VALUES(88,'D-price',14);
INSERT INTO "quality" VALUES(111,'A-color',10);
INSERT INTO "quality" VALUES(112,'B-style',10);
INSERT INTO "quality" VALUES(113,'C-feeling',10);
INSERT INTO "quality" VALUES(114,'A-Great',10);
INSERT INTO "quality" VALUES(115,'B-OK',10);
INSERT INTO "quality" VALUES(116,'C-Repair',10);
INSERT INTO "quality" VALUES(117,'D-Bad',10);
INSERT INTO "quality" VALUES(118,'D-price',10);
INSERT INTO "quality" VALUES(151,'A-Range',11);
INSERT INTO "quality" VALUES(152,'B-Range',11);
INSERT INTO "quality" VALUES(153,'C-Range',11);
INSERT INTO "quality" VALUES(154,'A-Great',11);
INSERT INTO "quality" VALUES(155,'B-OK',11);
INSERT INTO "quality" VALUES(156,'C-Repair',11);
INSERT INTO "quality" VALUES(157,'D-Bad',11);
INSERT INTO "quality" VALUES(158,'D-Range',11);
INSERT INTO "quality" VALUES(161,'A-color',12);
INSERT INTO "quality" VALUES(162,'B-style',12);
INSERT INTO "quality" VALUES(163,'C-feeling',12);
INSERT INTO "quality" VALUES(164,'A-Great',12);
INSERT INTO "quality" VALUES(165,'B-OK',2);
INSERT INTO "quality" VALUES(166,'C-Repair',12);
INSERT INTO "quality" VALUES(167,'D-Bad',12);
INSERT INTO "quality" VALUES(168,'D-price',12);
INSERT INTO "quality" VALUES(181,'A-color',4);
INSERT INTO "quality" VALUES(182,'B-style',4);
INSERT INTO "quality" VALUES(183,'C-feeling',4);
INSERT INTO "quality" VALUES(184,'A-Great',4);
INSERT INTO "quality" VALUES(185,'B-OK',4);
INSERT INTO "quality" VALUES(186,'C-Repair',4);
INSERT INTO "quality" VALUES(187,'D-Bad',4);
INSERT INTO "quality" VALUES(188,'D-price',4);
INSERT INTO "quality" VALUES(281,'A-color',5);
INSERT INTO "quality" VALUES(282,'B-style',5);
INSERT INTO "quality" VALUES(283,'C-feeling',5);
INSERT INTO "quality" VALUES(284,'A-Great',5);
INSERT INTO "quality" VALUES(285,'B-OK',5);
INSERT INTO "quality" VALUES(286,'C-Repair',5);
INSERT INTO "quality" VALUES(287,'D-Bad',5);
INSERT INTO "quality" VALUES(288,'D-price',5);
INSERT INTO "quality" VALUES(311,'A-color',9);
INSERT INTO "quality" VALUES(312,'B-style',9);
INSERT INTO "quality" VALUES(313,'C-feeling',9);
INSERT INTO "quality" VALUES(314,'A-Great',9);
INSERT INTO "quality" VALUES(315,'B-OK',9);
INSERT INTO "quality" VALUES(316,'C-Repair',9);
INSERT INTO "quality" VALUES(317,'D-Bad',9);
INSERT INTO "quality" VALUES(318,'D-price',9);
INSERT INTO "quality" VALUES(381,'A-color',6);
INSERT INTO "quality" VALUES(382,'B-style',6);
INSERT INTO "quality" VALUES(383,'C-feeling',6);
INSERT INTO "quality" VALUES(384,'A-Great',6);
INSERT INTO "quality" VALUES(385,'B-OK',6);
INSERT INTO "quality" VALUES(386,'C-Repair',6);
INSERT INTO "quality" VALUES(387,'D-Bad',6);
INSERT INTO "quality" VALUES(388,'D-price',6);
INSERT INTO "quality" VALUES(481,'A-color',15);
INSERT INTO "quality" VALUES(482,'B-style',15);
INSERT INTO "quality" VALUES(483,'C-feeling',15);
INSERT INTO "quality" VALUES(484,'A-Great',15);
INSERT INTO "quality" VALUES(485,'B-OK',15);
INSERT INTO "quality" VALUES(486,'C-Repair',15);
INSERT INTO "quality" VALUES(487,'D-Bad',15);
INSERT INTO "quality" VALUES(488,'D-price',15);
CREATE TABLE detail
(
classNo integer not null,/*班次表号*/
employeeNo integer not null,   /*被登记的员工号*/
workTypeNo integer not null,    /*工种号*/
concreteData text not null   /*具体数据*/
);
INSERT INTO "detail" VALUES(154,61,0,'1,5;4,3;');
INSERT INTO "detail" VALUES(160,3,2,'1,8;2,4;3,4;48,1;');
INSERT INTO "detail" VALUES(161,3,3,'1,8;2,4;26,4;48,4;');
INSERT INTO "detail" VALUES(158,3,4,'1,8;2,4;3,4;48,3;');
INSERT INTO "detail" VALUES(159,3,3,'1,8;2,4;33,4;48,4;');
INSERT INTO "detail" VALUES(156,6,3,'1,8;2,4;3,4;4,4;');
INSERT INTO "detail" VALUES(157,6,3,'1,8;2,14;3,4;4,4;');
INSERT INTO "detail" VALUES(1,6,2,'16,3;17,3;18,5;');
INSERT INTO "detail" VALUES(1,5,2,'16,1;17,3;18,3;');
INSERT INTO "detail" VALUES(4,1,1,'4,2;5,5;');
CREATE TABLE plant
(
plantNo text primary key,
plantName text not null,
plantPosition text not null,
managerNo text not null
);
INSERT INTO "plant" VALUES('1','1号车间','A区','1');
INSERT INTO "plant" VALUES('2','2号车间','B区','2');
INSERT INTO "plant" VALUES('3','3号车间','C区','3');
INSERT INTO "plant" VALUES('4','4号车间','D区','4');
INSERT INTO "plant" VALUES('5','5号车间','E区','5');
INSERT INTO "plant" VALUES('6','6号车间','F区','6');
INSERT INTO "plant" VALUES('8','8-plant','A-District','8');
INSERT INTO "plant" VALUES('9','8-plant','A-District','9');
INSERT INTO "plant" VALUES('10','10-Plant','A-District','10');
INSERT INTO "plant" VALUES('7','10-Plant','A-District','7');
INSERT INTO "plant" VALUES('11','11-Plant','A-District','11');
INSERT INTO "plant" VALUES('12','13-Plant','A-District','12');
INSERT INTO "plant" VALUES('13','13-Plant','A-District','13');
INSERT INTO "plant" VALUES('14','14-Plant','A-District','14');
INSERT INTO "plant" VALUES('15','15-Plant','A-District','15');
INSERT INTO "plant" VALUES('0','unknown','unknown','0');
CREATE TABLE employee
(
 employeeNo integer primary key,
 name text not null,
 pwd text not null,
 position interger ,
 plantNo integer ,
 workTypeNo integer
);
INSERT INTO "employee" VALUES(0,'ii','123',55,9,9);
INSERT INTO "employee" VALUES(2,'bb','123',55,2,2);
INSERT INTO "employee" VALUES(3,'cc','123',55,3,3);
INSERT INTO "employee" VALUES(4,'dd','123',55,4,4);
INSERT INTO "employee" VALUES(5,'ee','123',55,5,5);
INSERT INTO "employee" VALUES(6,'ff','123',55,6,6);
INSERT INTO "employee" VALUES(7,'gg','123',55,10,0);
INSERT INTO "employee" VALUES(8,'hh','123',55,8,0);
INSERT INTO "employee" VALUES(10,'jj','123',55,10,10);
INSERT INTO "employee" VALUES(11,'kk','123',55,11,0);
INSERT INTO "employee" VALUES(12,'ll','123',55,12,12);
INSERT INTO "employee" VALUES(13,'mm','123',55,13,13);
INSERT INTO "employee" VALUES(14,'nn','123',55,14,14);
INSERT INTO "employee" VALUES(15,'oo','123',55,15,15);
INSERT INTO "employee" VALUES(21,'lotus','123',2,1,1);
INSERT INTO "employee" VALUES(22,'lily','123',2,2,2);
INSERT INTO "employee" VALUES(23,'rose','123',2,3,3);
INSERT INTO "employee" VALUES(24,'apple','123',2,4,4);
INSERT INTO "employee" VALUES(25,'pear','123',2,5,5);
INSERT INTO "employee" VALUES(26,'banana','123',2,6,6);
INSERT INTO "employee" VALUES(27,'black','123',2,7,7);
INSERT INTO "employee" VALUES(28,'blue','123',3,8,8);
INSERT INTO "employee" VALUES(29,'pink','123',3,9,9);
INSERT INTO "employee" VALUES(30,'white','123',3,10,10);
INSERT INTO "employee" VALUES(31,'red','123',4,11,11);
INSERT INTO "employee" VALUES(32,'green','123',4,12,12);
INSERT INTO "employee" VALUES(33,'purple','123',5,13,13);
INSERT INTO "employee" VALUES(34,'grey','123',5,14,14);
INSERT INTO "employee" VALUES(35,'lightblue','123',5,15,15);
INSERT INTO "employee" VALUES(66,'jl','123',66,66,66);
INSERT INTO "employee" VALUES(77,'fc','123',77,77,77);
INSERT INTO "employee" VALUES(88,'zlb','123',88,88,88);
INSERT INTO "employee" VALUES(96,'joy','123',9,99,99);
INSERT INTO "employee" VALUES(97,'sad','123',9,99,99);
INSERT INTO "employee" VALUES(98,'happy','123',9,99,99);
INSERT INTO "employee" VALUES(99,'zld','123',99,99,99);
CREATE TABLE position
(
positionNo integer primary key,/*ְλ��*/
positionName text not null/*ְλ����
*/);
INSERT INTO "position" VALUES(0,'unknown');
INSERT INTO "position" VALUES(1,'worker');
INSERT INTO "position" VALUES(2,'worker');
INSERT INTO "position" VALUES(3,'worker');
INSERT INTO "position" VALUES(9,'qm');
INSERT INTO "position" VALUES(55,'manager');
INSERT INTO "position" VALUES(66,'boss');
INSERT INTO "position" VALUES(77,'analysis');
INSERT INTO "position" VALUES(88,'adm');
INSERT INTO "position" VALUES(99,'qmm');
CREATE TABLE class
(
classNo integer primary key autoincrement,
qmEmployeeNo text not null,
beginTime text not null,
endTime text not null,
classRange text not null,
plantNo integer not null,
crStatus text not null
);
INSERT INTO "class" VALUES(1,'1','2013-04-21 02:44:01','2013-04-21 02:44:01','amClass',1,'N');
INSERT INTO "class" VALUES(2,'96','2013-04-21 05:07:12','2013-04-21 05:07:12','pmClass',7,'N');
INSERT INTO "class" VALUES(3,'96','2013-04-21 05:15:34','2013-04-21 05:15:34','pmClass',1,'N');
INSERT INTO "class" VALUES(4,'96','2013-04-21 05:16:14','2013-04-21 05:16:14','pmClass',1,'N');
CREATE TABLE res(resNo integer not null,resMakerNo integer,resText text,positionNo integer);
INSERT INTO "res" VALUES(1,77,'quality of T-shirt is too bad today',66);
INSERT INTO "res" VALUES(2,77,'the A rate of suits is too low',66);
INSERT INTO "res" VALUES(3,77,'the coat should be stopped now',66);
INSERT INTO "res" VALUES(0,77,'unknowned',66);
DELETE FROM sqlite_sequence;
INSERT INTO "sqlite_sequence" VALUES('class',4);
COMMIT;

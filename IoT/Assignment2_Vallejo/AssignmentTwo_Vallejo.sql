/*Section 1*/

create database Vallejo_IOTDATABASE

/*Section 4*/
select * from Vallejo_IOTDATABASE;

select DEVICE_ID, TEMPERATURE_FAR, INSERT_DATA from Vallejo_IOTDATABASE;

select max(TEMPERATURE_CEL) from Vallejo_IOTDATABASE group by DEVICE_ID;
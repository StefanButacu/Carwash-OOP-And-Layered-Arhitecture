# Carwash-OOP-And-Layered-Arhitecture
Carwash app design using OOP principles and Qt framework

1. Layerd Arhitecture 
    - Domain
    - Repository  
    - Service
    - View
2. Notable design patterns
    - Command design ( illustrated with Undo functionality where i declared a abstract class UndoAction and 3 inheriting classes UndoAdd, UndoDelete, UndoUpdate)
    - Observer pattern ( Changes inside the CarWash class should be visible to all new application windows)
    -  Model-View-Controller ( A class is resposible to get the data from Repository and to pass it to the user depending on his request (don't load all entities at the start of app)) 
   
* Start app
![Start app](https://github.com/StefanButacu/Carwash-OOP-And-Layered-Arhitecture/blob/master/Photos/photo1.JPG)
* Warning
![Warning](https://github.com/StefanButacu/Carwash-OOP-And-Layered-Arhitecture/blob/master/Photos/photo2.JPG)
![Start game](https://github.com/StefanButacu/Carwash-OOP-And-Layered-Arhitecture/blob/master/Photos/photo6.JPG)

* Washlist
![Wash list](https://github.com/StefanButacu/Carwash-OOP-And-Layered-Arhitecture/blob/master/Photos/photo3.JPG)
* Observer Pattern
![Observer](https://github.com/StefanButacu/Carwash-OOP-And-Layered-Arhitecture/blob/master/Photos/photo4.JPG)
* Wash menu
![Observer](https://github.com/StefanButacu/Carwash-OOP-And-Layered-Arhitecture/blob/master/Photos/photo5.JPG)

In this phase I have added more commands than phase 1
## To simply run
  build the project using **make** then enter below command
  
  ./utms.out </path/to/majors.csv> </path/to/students.csv> </path/to/courses.csv> </path/to/teachers.csv>

## What you can do:
| 📝 Command Description                                | 🔧 API Command                                                                                          |
|------------------------------------------------------|---------------------------------------------------------------------------------------------------------|
| Login                                                | `POST login ? id <id> password <password>`                                                              |
| Logout                                               | `POST logout ?`                                                                                         |
| List of courses presented                            | `GET courses ? id <id>`                                                                                 |
| Course description                                   | `GET courses ? id <id>`                                                                                 |
| List of all courses presented                        | `GET courses ?`                                                                                         |
| Create post                                          | `POST post ? title <title> message <message>`                                                           |
| Create post with an image                            | `POST post ? title <title> message <message> image <image_address>`                                     |
| Delete post                                          | `DELETE post ? id <id>`                                                                                 |
| See personal page of a user                          | `GET personal_page ? id <id>`                                                                           |
| See a user's post                                    | `GET post ? id <id> post_id <post_id>`                                                                  |
| Follow another user                                  | `POST connect ? id <id>`                                                                                |
| See notifications                                    | `GET notification ?`                                                                                    |
| Add a profile picture                                | `POST profile_photo ? photo <photo_address>`                                                            |
| Add a course (only for the manager)                 | `POST course_offer ? course_id <course_id> professor_id <professor_id> capacity <capacity> time <time> exam_date <exam_date> class_number <class_number>` |
| Create a post in course info channel                 | `POST course_post ? id <id> title <title> message <message> image <image_address>`                      |
| See a course info channel                            | `GET course_channel ? id <id>`                                                                          |
| See a post from course info channel                  | `GET course_post ? id <id> post_id <post_id>`                                                           |
| Create a teacher assistant form                      | `POST ta_form ? course_id <course_id> message "<message>"`                                              |
| Close a teacher assistant form                       | `POST close_ta_form ? id <id>`                                                                          |
| Send TA request (only for students)                  | `POST ta_request ? professor_id <professor_id> form_id <form_id>`                                       |
| Enroll in a course (only for students)              | `PUT my_courses ? id <id>`                                                                              |
| Dropout from a course (only for students)           | `DELETE my_courses ? id <id>`                                                                           |
| See all enrolled courses (only for students)        | `GET my_courses ?`                                                                                      |

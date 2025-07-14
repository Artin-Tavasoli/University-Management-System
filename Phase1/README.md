## To simply run
  build the project using **make** then enter below command
  
  ./utms.out </path/to/majors.csv> </path/to/students.csv> </path/to/courses.csv> </path/to/teachers.csv>

## What you can do:
| 📝 Command Description                                | 🔧 API Command                                                                                          |
|------------------------------------------------------|---------------------------------------------------------------------------------------------------------|
| Logout                                               | `POST logout ?`                                                                                         |
| List of courses presented                            | `GET courses ? id <id>`                                                                                 |
| Course description                                   | `GET courses ? id <id>`                                                                                 |
| List of all courses presented                        | `GET courses ?`                                                                                         |
| Create post                                          | `POST post ? title <title> message <message>`                                                           |
| Delete post                                          | `DELETE post ? id <id>`                                                                                 |
| See personal page of a user                          | `GET personal_page ? id <id>`                                                                           |
| See a user's post                                    | `GET post ? id <id> post_id <post_id>`                                                                  |
| Follow another user                                  | `POST connect ? id <id>`                                                                                |
| See notifications                                    | `GET notification ?`                                                                                    |
| Add a course (only for the manager)                 | `POST course_offer ? course_id <course_id> professor_id <professor_id> capacity <capacity> time <time> exam_date <exam_date> class_number <class_number>` |
| Enroll a course (only for the students)             | `PUT my_courses ? id <id>`                                                                              |
| Dropout from a course (only for the students)       | `DELETE my_courses ? id <id>`                                                                           |
| See all courses enrolled in (only for the students) | `GET my_courses ?`                                                                                      |

📆 Time format: `<week_day>:<start_time>-<end_time>`

📅 Date format: `<year>/<month>/<day>`

package project.backend;

import lombok.RequiredArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;


@RestController
@RequiredArgsConstructor
@CrossOrigin
public class UserController {

    @Autowired
    private UserService userService;

    @PostMapping("/add")
    public Employee addUser(@RequestBody Employee employee) {
        return userService.addUser(employee);
    }

    @GetMapping("/id")
    public Employee getUserById(@RequestParam long id) {
        return userService.getUser(id);
    }

    @GetMapping("/rfid")
    public Employee getUserByRfid(@RequestParam String rfid) {
        return userService.getUserByRfid(rfid);
    }

    @GetMapping("/ser")
    public Employee getUserBySurname(@RequestParam String lastName) {
        return userService.getUserByLastName(lastName);
    }

    @GetMapping("/name")
    public Employee getUserByName(@RequestParam String firstName) {
        return userService.getUserByFirstName(firstName);
    }

    @DeleteMapping("/{id}")
    public void deleteUserById(@PathVariable Long id) {
        userService.deleteById(id);
    }
}

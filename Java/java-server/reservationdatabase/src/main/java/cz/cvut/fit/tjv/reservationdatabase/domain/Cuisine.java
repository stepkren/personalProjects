package cz.cvut.fit.tjv.reservationdatabase.domain;

import jakarta.persistence.*;
import jakarta.validation.constraints.NotBlank;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.util.List;

@Entity
@Table(name = "Cuisine")
@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class Cuisine {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE)
    @Column(name = "cuisine_id")
    private Long cuisineId;

    // The country this cuisine belongs to, cannot be left blank, must be unique
    @Column(name = "country", unique = true)
    @NotBlank
    private String country;

    // List of restaurants that the cuisine is cooked at, represented as a Many-To-Many relationship
    @OneToMany(targetEntity = Restaurant.class, mappedBy = "cooks", orphanRemoval = true)
    private List<Restaurant> isCookedAt;

}

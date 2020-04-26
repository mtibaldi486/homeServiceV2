package home.service.java;

public class Prestation {
    private String id_prestation;
    private String nom;
    private String description;
    private String categorie_ville;
    private String categorie_nom;
    private String bareme_id_bareme;

    public Prestation(){

    }

    public Prestation(String id, JDBC DataManager){
        this.id_prestation = id;
        String[][] array = DataManager.getDataTable("SELECT * FROM prestation WHERE id_prestation = " + id, 0);

        this.nom = array[0][1];
        this.description = array[0][2];
        this.categorie_ville = array[0][3];
        this.categorie_nom = array[0][4];
        this.bareme_id_bareme = array[0][5];
    }

    public String getId_prestation() {
        return id_prestation;
    }

    public void setId_prestation(String id_prestation) {
        this.id_prestation = id_prestation;
    }

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getCategorie_ville() {
        return categorie_ville;
    }

    public void setCategorie_ville(String categorie_ville) {
        this.categorie_ville = categorie_ville;
    }

    public String getCategorie_nom() {
        return categorie_nom;
    }

    public void setCategorie_nom(String categorie_nom) {
        this.categorie_nom = categorie_nom;
    }

    public String getBareme_id_bareme() {
        return bareme_id_bareme;
    }

    public void setBareme_id_bareme(String bareme_id_bareme) {
        this.bareme_id_bareme = bareme_id_bareme;
    }
}

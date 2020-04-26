package home.service.java;

public class Bareme {
    private String id_bareme;
    private String unite;
    private float prix_unite;
    private float prix_unit_recurrent;
    private float nb_unit_minimum;
    private float time_per_unit;

    public Bareme(String id, JDBC DataManager){
        this.id_bareme = id;
        String[][] array = DataManager.getDataTable("SELECT * FROM bareme WHERE id_bareme = "+id,0);
        if(array!=null) {
            this.unite = array[0][1];
            this.prix_unite = Float.parseFloat(array[0][2]);
            this.prix_unit_recurrent = Float.parseFloat(array[0][3]);
            this.nb_unit_minimum = Float.parseFloat(array[0][4]);
            this.time_per_unit = Float.parseFloat(array[0][2]);
        }
    }

    public Bareme checkPrice(Prestataire prestataire){
        if(prestataire.getPrix_heure() * 1.3 > this.prix_unite) {
            this.setPrix_unite((float)(prestataire.getPrix_heure() * 1.3));
            if(prestataire.getPrix_recurrent() * 1.3 > this.prix_unit_recurrent){
                this.setPrix_unit_recurrent((float)(prestataire.getPrix_recurrent() * 1.3));
            }
            if(prestataire.getNb_heure_min() > this.nb_unit_minimum){
                this.setNb_unit_minimum(prestataire.getNb_heure_min());
            }
        }
        return this;
    }

    public String getId_bareme() {
        return id_bareme;
    }

    public void setId_bareme(String id_bareme) {
        this.id_bareme = id_bareme;
    }

    public String getUnite() {
        return unite;
    }

    public void setUnite(String unite) {
        this.unite = unite;
    }

    public float getPrix_unite() {
        return prix_unite;
    }

    public void setPrix_unite(float prix_unite) {
        this.prix_unite = prix_unite;
    }

    public float getPrix_unit_recurrent() {
        return prix_unit_recurrent;
    }

    public void setPrix_unit_recurrent(float prix_unit_recurrent) {
        this.prix_unit_recurrent = prix_unit_recurrent;
    }

    public float getNb_unit_minimum() {
        return nb_unit_minimum;
    }

    public void setNb_unit_minimum(float nb_unit_minimum) {
        this.nb_unit_minimum = nb_unit_minimum;
    }

    public float getTime_per_unit() {
        return time_per_unit;
    }

    public void setTime_per_unit(float time_per_unit) {
        this.time_per_unit = time_per_unit;
    }

    }


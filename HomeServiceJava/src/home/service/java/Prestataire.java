package home.service.java;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Prestataire {
    private String id_prestataire;
    private String nom;
    private String tel_mobile;
    private String tel_fixe;
    private String adresse_entreprise;
    private String url_qrcode;
    private String prix_heure;
    private String supplement;
    private String company_name;
    private String code_postal;
    private String email;
    private String nb_heure_min;
    private String prix_recurrent;
    private String categorie_ville;
    private String categorie_nom;

    public Prestataire(){

    }

    public Prestataire(String id, JDBC DataManager){
        this.id_prestataire = id;
        String[][] array = DataManager.getDataTable("SELECT * FROM prestataire WHERE id_prestataire = " + id, 0);

        this.nom = array[0][1];
        this.tel_mobile = array[0][2];
        this.tel_fixe = array[0][3];
        this.adresse_entreprise = array[0][4];
        this.url_qrcode = array[0][5];
        this.prix_heure = array[0][6];
        this.supplement = array[0][7];
        this.company_name = array[0][8];
        this.code_postal = array[0][9];
        this.email = array[0][10];
        this.nb_heure_min = array[0][11];
        this.prix_recurrent = array[0][12];
        this.categorie_ville = array[0][13];
        this.categorie_nom = array[0][14];
    }

    public String getId_prestataire() {
        return id_prestataire;
    }

    public void setId_prestataire(String id_prestataire) {
        this.id_prestataire = id_prestataire;
    }

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public String getTel_mobile() {
        return tel_mobile;
    }

    public void setTel_mobile(String tel_mobile) {
        this.tel_mobile = tel_mobile;
    }

    public String getTel_fixe() {
        return tel_fixe;
    }

    public void setTel_fixe(String tel_fixe) {
        this.tel_fixe = tel_fixe;
    }

    public String getAdresse_entreprise() {
        return adresse_entreprise;
    }

    public void setAdresse_entreprise(String adresse_entreprise) {
        this.adresse_entreprise = adresse_entreprise;
    }

    public String getUrl_qrcode() {
        return url_qrcode;
    }

    public void setUrl_qrcode(String url_qrcode) {
        this.url_qrcode = url_qrcode;
    }

    public String getPrix_heure() {
        return prix_heure;
    }

    public void setPrix_heure(String prix_heure) {
        this.prix_heure = prix_heure;
    }

    public String getSupplement() {
        return supplement;
    }

    public void setSupplement(String supplement) {
        this.supplement = supplement;
    }

    public String getCompany_name() {
        return company_name;
    }

    public void setCompany_name(String company_name) {
        this.company_name = company_name;
    }

    public String getCode_postal() {
        return code_postal;
    }

    public void setCode_postal(String code_postal) {
        this.code_postal = code_postal;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getNb_heure_min() {
        return nb_heure_min;
    }

    public void setNb_heure_min(String nb_heure_min) {
        this.nb_heure_min = nb_heure_min;
    }

    public String getPrix_recurrent() {
        return prix_recurrent;
    }

    public void setPrix_recurrent(String prix_recurrent) {
        this.prix_recurrent = prix_recurrent;
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

}
